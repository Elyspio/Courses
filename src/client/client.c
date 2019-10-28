#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "../common/const.h"


int main() {
	int client_socket_fd = connect_client();

	send_receive_message(client_socket_fd);
	printf("\n");
	send_receive_name(client_socket_fd);
	printf("\n");
	send_receive_calcul(client_socket_fd);
	printf("\n");
	send_receive_color(client_socket_fd);

	close(client_socket_fd);
}

/**
 * @return File descriptor of the socket
 * @return -1 if could not connect to the server
 * @return -2 if could not create the socket
 */
int connect_client() {
	int socketfd;

	struct sockaddr_in server_addr;

	/*
	 * Creation d'un socket
	 */
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		perror("socket");
		return -2;
	}

	//détails du serveur (adresse et port)
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//demande de connection au serveur
	int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
	if (connect_status < 0) {
		perror("server connection");
		return -1;
	}
	return socketfd;
}

/**
 *
 * @param socketfd
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_message(int socketfd) {

	const int prompt_length = strlen(PROMPT_MESSAGE);
	const int message_length = DATA_LENGTH - prompt_length;

	char *data = calloc(DATA_LENGTH, sizeof(char));

	char message[message_length];
	printf("Your message (max %d characters): ", message_length);
	fgets(message, DATA_LENGTH, stdin);
	strcpy(data, PROMPT_MESSAGE);
	strcat(data, message);

	printf("Message to send: %s", data);

	int write_status = write(socketfd, data, strlen(data));
	if (write_status < 0) {
		perror("Error: write");
		return -1;
	}

	memset(data, 0, DATA_LENGTH);
	int read_status = read(socketfd, data, DATA_LENGTH);
	if (read_status < 0) {
		perror("Error: read");
		return -2;
	}

	printf("Recieved message from server: %s\n", data + prompt_length);
	free(data);
	return 0;
}

int send_receive_calcul(int socketfd) {
	printf("Send a compute: < + -  / * > <a> <b> ");

	char *data = calloc(DATA_LENGTH, sizeof(char));
	int prompt_length = strlen(PROMPT_CALCUL);
	char *message = malloc((DATA_LENGTH - prompt_length) * sizeof(char));
	fgets(message, DATA_LENGTH - prompt_length, stdin);
	message[DATA_LENGTH - prompt_length - 1] = '\0';
	strncpy(data, PROMPT_CALCUL, prompt_length);
	strcat(data, message);

	int write_status = write(socketfd, data, strlen(data));
	if (write_status < 0) {
		perror("Error: write");
		return -1;
	}

	memset(data, 0, DATA_LENGTH);
	int read_status = read(socketfd, data, DATA_LENGTH);
	if (read_status < 0) {
		perror("Error: read");
		return -2;
	}

	printf("Result from server: %s\n", data + prompt_length);
	free(data);

	return 0;
}

int send_receive_color(int socketfd) {
	printf("Send colors: nb_colors, color1, colorX, ...");

	char *data = calloc(DATA_LENGTH, sizeof(char));
	int prompt_length = strlen(PROMPT_COLOR);
	char *message = malloc((DATA_LENGTH - prompt_length) * sizeof(char));
	fgets(message, DATA_LENGTH - prompt_length, stdin);
	message[DATA_LENGTH - prompt_length - 1] = '\0';
	strncpy(data, PROMPT_COLOR, prompt_length);
	strcat(data, message);

	int write_status = write(socketfd, data, strlen(data));
	if (write_status < 0) {
		perror("Error: write");
		return -1;
	}

	memset(data, 0, DATA_LENGTH);
	int read_status = read(socketfd, data, DATA_LENGTH);
	if (read_status < 0) {
		perror("Error: read");
		return -2;
	}

	printf("Response from server: %s\n", data + prompt_length);
	free(data);

	return 0;
}

int send_receive_name(int socketfd) {
	const int prompt_length = strlen(PROMPT_NAME);
	const int message_length = DATA_LENGTH - prompt_length;

	char *data = calloc(DATA_LENGTH, sizeof(char));

	char message[message_length];

	gethostname(message, 1023);

	strcpy(data, PROMPT_NAME);
	strcat(data, message);


	int write_status = write(socketfd, data, strlen(data));
	if (write_status < 0) {
		perror("Error: write");
		return -1;
	}

	memset(data, 0, DATA_LENGTH);
	int read_status = read(socketfd, data, DATA_LENGTH);
	if (read_status < 0) {
		perror("Error: read");
		return -2;
	}

	printf("Recieved name from server: %s\n", data + prompt_length);
	free(data);
	return 0;
}