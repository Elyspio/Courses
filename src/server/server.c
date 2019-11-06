//
// Created by elyspio on 28/09/2019.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "server.h"
#include "../common/const.h"
#include "../common/json.h"
#include "../common/enum.h"


/**
 *
 * @param client_socket_fd
 * @param message
 * @return 0 if everything has worked correctly
 * @return -1 if could not write data into the socket
 */
int _response(int client_socket_fd, char* message) {
	int data_size = write(client_socket_fd, (void*) message, strlen(message));

	if (data_size < 0) {
		perror("erreur ecriture");
		return -1;
	}
	return 0;
}


int main() {


	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	printf("Server started at %d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

	int client_socket_fd = listen_client();
	if (client_socket_fd > 0) {

		while (true) {
			handle_request(client_socket_fd);
		}

	}


	return 0;
}

/**
 *
 * @return 0 if everything has worked correctly
 * @return -1 if could not open a socket
 * @return -2 if could not bind socket and the server
 * @return -3 if could not connect to a client
 *
 */
int listen_client() {
	int socketfd;
	int bind_status;

	struct sockaddr_in server_addr;

	/*
	 * Creation d'un socket
	 */
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		perror("Unable to open a socket");
		return -1;
	}

	int option = 1;
	setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	//détails du serveur (adresse et port)
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind_status = bind(socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if (bind_status < 0) {
		perror("Error: bind");
		return -2;
	}

	listen(socketfd, 10);
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	// nouvelle connection de client
	int client_socket_fd = accept(socketfd, (struct sockaddr*) &client_addr, &client_addr_len);
	if (client_socket_fd < 0) {
		perror("Error: Accept");
		return -3;
	}

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Client connected at %d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

	return client_socket_fd;
}


int handle_request(int socket_fd) {

	char* data = calloc(DATA_LENGTH, sizeof(char));

	do {
		int data_size = read(socket_fd, (void*) data, DATA_LENGTH);

		if (data == NULL || strncmp("", data, 1) == 0) {
			exit(0);
		}

		if (data_size <= 0) {
			perror("erreur lecture");
			return (EXIT_FAILURE);
		}

	} while (strcmp("", data) == 0);


	int error_code = 0;
	json_data json;

	deserialize(&json, data);
	code code = getCode(json.code);
	switch (code) {

		case MESSAGE:
			error_code = _handle_message(socket_fd, &json);
			break;
		case CALCUL:
			error_code = _handle_calcul(socket_fd, &json);
			break;
		case COLOR:
			error_code = _handle_color(socket_fd, &json);
			break;
		case NAME:
			error_code = _handle_name(socket_fd, &json);
			break;
		case NOT_IDENTIFIED:
		default:
			_handle_error(socket_fd, "Could not identify the code of your message.");
			break;

	}
	if (error_code != 0) {
		_handle_error(socket_fd, "Error while handling request.");

	}
	free(data);
	return 0;
}

int _handle_error(int socket_fd, char* message) {
	char* data = calloc(DATA_LENGTH, sizeof(char));
	strncpy(data, PROMPT_ERROR, sizeof(PROMPT_ERROR));
	strncat(data, message, DATA_LENGTH - strlen(message));
	return _response(socket_fd, data);
}

int _handle_message(int socket_fd, json_data* json) {

	if (json->data_length == 1) {
		printf("Message recieved from client: %s\n", json->data[0]);
		int prompt_length = strlen(PROMPT_MESSAGE);

		printf("Please enter the response: ");
		char* response_message = calloc(DATA_LENGTH - prompt_length, sizeof(char));
		fgets(response_message, DATA_LENGTH - prompt_length, stdin);
		response_message[strlen(response_message) - 1] = '\0';

		strncpy(json->data[0], response_message, strlen(response_message));

		char* data = serialize(json);

		return _response(socket_fd, data);
	}

	return _handle_error(socket_fd, "to handle a message, we need only 1 argument: message");


}

int _handle_calcul(int socket_fd, json_data* json) {
	if (json->data_length == 3) {
		double a = strtod(json->data[1], NULL);
		double b = strtod(json->data[2], NULL);
		char operator = json->data[0][0];
		char* error_str;
		double result = a;
		switch (operator) {
			case '+':
				result += b;
				break;
			case '-':
				result -= b;
				break;
			case '/':
				result /= b;
				break;
			case '*':
				result *= b;
				break;

			default:
				error_str = calloc(100, sizeof(char));
				sprintf(error_str, "Unknown operator '%c' could not continu", operator);
				return _handle_error(socket_fd, error_str);
		}
		json->data_length = 1;
		sprintf(json->data[0], "%lf", result);

		char* data = calloc(DATA_LENGTH, sizeof(char));
		strcpy(data, serialize(json));
		return _response(socket_fd, data);
	}
	return _handle_error(socket_fd, "to handle a calcul, we need 3 argument: operator nbA, nbB");
}


void plot(struct json_data* json) {

	//Extraire le compteur et les couleurs RGB
	FILE* p = popen("gnuplot -persist", "w");
	printf("Plot");
	fprintf(p, "set xrange [-15:15]\n");
	fprintf(p, "set yrange [-15:15]\n");
	fprintf(p, "set style fill transparent solid 0.9 noborder\n");
	fprintf(p, "set title 'Top %d colors'\n", json->data_length);
	fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
	for (int i = 0; i < json->data_length; i++) {
		int divide = 360 / json->data_length;
		fprintf(p, "0 0 %d %d %d 0x%s\n", divide, (i - 1) * divide, i * divide, json->data[i] + 1);
	}
	fprintf(p, "e\n");
	printf("Plot: FIN\n");
	pclose(p);
}


int _handle_color(int socket_fd, json_data* json) {

	if (json->data_length >= 1) {
		plot(json);
		json->data_length = 1;
		json->data[0] = "colors are printed on the server";
		return _response(socket_fd, serialize(json));

	}
	return _handle_error(socket_fd, "to handle colors, we need at least one argument: nbColors [#color1 #color2]");
}

int _handle_name(int socket_fd, json_data* json) {
	if (json->data_length == 1) {
		printf("Client's name: %s\n", json->data[0]);
		return _response(socket_fd, serialize(json));
	}
	return _handle_error(socket_fd, "to handle name, we need one argument: name");

}




