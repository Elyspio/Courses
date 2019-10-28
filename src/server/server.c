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
#include "../common/tools.h"
#include "../common/const.h"


/**
 *
 * @param client_socket_fd
 * @param data
 * @return 0 if everything has worked correctly
 * @return -1 if could not write data into the socket
 */
int _response(int client_socket_fd, char *data) {
	int data_size = write(client_socket_fd, (void *) data, strlen(data));

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

	bind_status = bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
	if (bind_status < 0) {
		perror("Error: bind");
		return -2;
	}

	listen(socketfd, 10);
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);

	// nouvelle connection de client
	int client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
	if (client_socket_fd < 0) {
		perror("Error: Accept");
		return -3;
	}

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Client connected at %d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

	return client_socket_fd;
}


code getCode(char *data) {

	code code = NOT_IDENTIFIED;
	if (strncmp(data, PROMPT_MESSAGE, strlen(PROMPT_MESSAGE)) == 0) {
		code = MESSAGE;
	}
	if (strncmp(data, PROMPT_COLOR, strlen(PROMPT_COLOR)) == 0) {
		code = COLOR;
	}
	if (strncmp(data, PROMPT_CALCUL, strlen(PROMPT_CALCUL)) == 0) {
		code = CALCUL;
	}
	if (strncmp(data, PROMPT_NAME, strlen(PROMPT_NAME)) == 0) {
		code = NAME;
	}
	return code;


}


int handle_request(int socket_fd) {

	char *data = calloc(DATA_LENGTH, sizeof(char));

	int data_size = read(socket_fd, (void *) data, DATA_LENGTH);

	if (data_size < 0) {
		perror("erreur lecture");
		return (EXIT_FAILURE);
	}

	int error_code = 0;
	code code = getCode(data);
	switch (code) {

		case MESSAGE:
			error_code = _handle_message(socket_fd, data + strlen(PROMPT_MESSAGE));
			break;
		case CALCUL:
			error_code = _handle_calcul(socket_fd, data + strlen(PROMPT_CALCUL));
			break;
		case COLOR:
			error_code = _handle_color(socket_fd, data + strlen(PROMPT_COLOR));
			break;
		case NAME:
			error_code = _handle_name(socket_fd, data + strlen(PROMPT_NAME));
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

int _handle_error(int socket_fd, char *message) {
	char *data = calloc(DATA_LENGTH, sizeof(char));
	strncpy(data, PROMPT_ERROR, sizeof(PROMPT_ERROR));
	strncat(data, message, DATA_LENGTH - strlen(message));
	return _response(socket_fd, data);
}

int _handle_message(int socket_fd, char *data) {

	printf("Message recieved from client: %s", data);
	int prompt_length = strlen(PROMPT_MESSAGE);

	printf("Please enter the response: ");
	char *response_message = calloc(DATA_LENGTH - prompt_length, sizeof(char));
	fgets(response_message, DATA_LENGTH - prompt_length, stdin);
	response_message[strlen(response_message) - 1] = '\0';

	memset(data, 0, DATA_LENGTH);
	strncpy(data, PROMPT_MESSAGE, prompt_length);
	strcat(data, response_message);

	free(response_message);

	return _response(socket_fd, data);

}

int _handle_calcul(int socket_fd, char *data) {
	double a, b;
	char operator;
	sscanf(data, "%c %lf %lf", &operator, &a, &b);
	char *error_str;
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

	int prompt_length = strlen(PROMPT_CALCUL);
	char *response_message = calloc(DATA_LENGTH - prompt_length, sizeof(char));

	sprintf(response_message, "%lf", result);

	memset(data, 0, DATA_LENGTH);
	strncpy(data, PROMPT_CALCUL, prompt_length);
	strcat(data, response_message);

	free(response_message);

	return _response(socket_fd, data);
}

int _handle_color(int socket_fd, char *data) {
	int nb_colors;

	char *colors = calloc(DATA_LENGTH - strlen(PROMPT_COLOR), sizeof(char));
	sscanf(data, "%d %[^\n] ", &nb_colors, colors);

	// As task we store colors in column into the file.

	char *targets = " ";
	remove_all(colors, targets);
	slice(colors, 1, (int) strlen(colors));
	replace_all(colors, ',', '\n');

	FILE *file = fopen("color.txt", "a+");

	fwrite(colors, sizeof(char), strlen(colors), file);
	fwrite("\n", sizeof(char), 1, file);
	fflush(file);
	fclose(file);

	char *response = malloc(DATA_LENGTH);
	strncpy(response, PROMPT_COLOR, strlen(PROMPT_COLOR));
	strcat(response, "color(s) are saved on the server.");

	return _response(socket_fd, response);

}

int _handle_name(int socket_fd, char *data) {

	printf("Client's name: %s\n", data);
	char *response = malloc(DATA_LENGTH);
	strncpy(response, PROMPT_NAME, strlen(PROMPT_NAME));
	strcat(response, data);
	return _response(socket_fd, response);

	return 0;
}




