#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "../common/tools.h"
#include "../common/const.h"
#include "../common/enum.h"
#include "../common/json.h"
#include "couleur.h"
#include "bmp.h"

int main(int argc, char** argv) {
	int client_socket_fd = connect_client();


	disp_menu(client_socket_fd);

	close(client_socket_fd);
}


void disp_menu(int socked_fd) {
	bool run = true;
	while (run) {
		printf("\nWhat do you want to do ?\n");
		printf("\t%d: Close the connection\n", MENU_CHOICE_EXIT);
		printf("\t%d: Send a message\n", MENU_CHOICE_MESSAGE);
		printf("\t%d: Send the machine's name\n", MENU_CHOICE_NAME);
		printf("\t%d: Send a compute\n", MENU_CHOICE_COMPUTE);
		printf("\t%d: Analyse an image\n", MENU_CHOICE_COLOR);
//        fflush(stdout);
		int choice = -1;
		string choice_str = calloc(4, sizeof(char));
		while (choice < 1 || choice > 5) {
//        	fflush(stdin);
			fgets(choice_str, 4, stdin);
			choice = (int) strtol(choice_str, NULL, 10);
		}

		switch (choice) {

			case MENU_CHOICE_EXIT:
				run = false;
				break;

			case MENU_CHOICE_MESSAGE:
				send_receive_message(socked_fd);
				break;

			case MENU_CHOICE_NAME:
				send_receive_name(socked_fd);
				break;

			case MENU_CHOICE_COMPUTE:
				send_receive_compute(socked_fd);
				break;

			case MENU_CHOICE_COLOR:
				send_receive_color(socked_fd);
				break;

			default:
				break;
		}
	}

}


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
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//demande de connection au serveur
	int connect_status = connect(socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
	if (connect_status < 0) {
		perror("server connection");
		return -1;
	}
	return socketfd;
}


int send_receive_message(int socketfd) {

	char* data = calloc(DATA_LENGTH, sizeof(char));

	char* message = malloc(MESSAGE_MAX_LENGH);
	printf("Your message (max %d characters): ", MESSAGE_MAX_LENGH);
	fgets(message, MESSAGE_MAX_LENGH, stdin);
	message[strlen(message) - 1] = '\0';

	json_data json = json_create(1);
	strcpy(json.code, CODE_MESSAGE);
	value v = value_create();
	strcpy(v.type, TYPE_STR);
	v.data = malloc(strlen(message));
	strcpy(v.data, message);
	json.values[0] = v;

	strcpy(data, serialize(&json));
	int write_status = write(socketfd, data, strlen(data));
	if (write_status < 0) {
		perror("Error: write");
		return -1;
	}

	json_free(&json);

	memset(data, 0, DATA_LENGTH);
	int read_status = read(socketfd, data, DATA_LENGTH);
	if (read_status < 0) {
		perror("Error: read");
		return -2;
	}

	json_data new_json = json_create(1);
	deserialize(&new_json, data);

	if (getCode(new_json.code) == MESSAGE) {
		if (new_json.data_length == 1 && strcmp(new_json.values[0].type, TYPE_STR) == 0) {
			printf("Recieved message from server: %s\n", (string) new_json.values[0].data);
			fflush(stdout);
		} else {
			perror("Error nb arguments in message response");
		}
	} else {
		fprintf(stderr, "Wrong code in response to a message:  %s", new_json.code);
	}

	json_free(&new_json);
	free(data);

	return 0;
}


int send_receive_compute(int socketfd) {

	char* data = calloc(DATA_LENGTH, sizeof(char));
	json_data json;
	json.code = NULL;
	json_create_ptr(&json, 3);

	strcpy(json.code, CODE_COMPUTE);

	printf("Send a compute: <operator> <nb_1> <nb_2> <nb_n>\n");
	printf("Operators available:"
	       "\n\t+   : add all numbers"
	       "\n\t-   : substract all numbers"
	       "\n\t*   : multiply all numbers"
	       "\n\t/   : divide all numbers"
	       "\n\tavg : average of all numbers"
	       "\n\tsd  : standard deviation of all numbers"
	       "\n\tmin : min from all numbers"
	       "\n\tmax : max from all numbers\n"
	);
	string s = malloc(16), s2 = malloc(MESSAGE_MAX_LENGH);
	scanf("%s %[^\n]", s, s2);

	value operator = value_create();
	strcpy(operator.type, TYPE_STR);
	operator.data = calloc(strlen(s), sizeof(char));
	strcpy(operator.type, TYPE_STR);
	strcpy(operator.data, s);
	json.values[0] = operator;

	char delemiter[1] = " ";
	char* ptr = strtok(s2, delemiter);
	int i = 1;
	while (ptr != NULL) {
		if (try_parse_number(ptr) > 0) {
			json.data_length = i + 1;
			json.values[i] = value_create();
			if (is_double(ptr)) {
				*(double*) json.values[i].data = strtod(ptr, NULL);
				strcpy(json.values[i].type, TYPE_DOUBLE);
			} else {
				*(int*) json.values[i].data = (int) strtod(ptr, NULL);
				strcpy(json.values[i].type, TYPE_INT);
			}
		} else {
			printf("%s is not a number", ptr);
		}
		i++;
		ptr = strtok(NULL, delemiter);
		if (ptr != NULL) {
			json.values = realloc(json.values, (i + 1) * sizeof(value));

		}

	}


	strcpy(data, serialize(&json));


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

	deserialize(&json, data);

	code code = getCode(json.code);
	if (code == CALCUL) {
		if (json.data_length == 1) {
			if (strcmp(json.values[0].type, TYPE_INT) == 0) {
				printf("Result from server: %d\n", *(int*) json.values[0].data);

			} else if (strcmp(json.values[0].type, TYPE_DOUBLE) == 0) {
				printf("Result from server: %lf\n", *(double*) json.values[0].data);
			} else {
				fprintf(stderr, "Error type of value in compute response");
			}
		} else {
			fprintf(stderr, "Wrong code in response to a message:  %s", json.code);
		}
		fflush(stdout);
		free(data);
		return 0;
	}

	return -3;

}

void analyse(char* pathname, char** colors, int nb_colors) {
	//compte de couleurs
	couleur_compteur* cc = analyse_bmp_image(pathname);

	char* temp_string = calloc(10, sizeof(char));

	//choisir nb_colors couleurs
	for (int count = 0; count < nb_colors && cc->size - count > 0; count++) {
		if (cc->compte_bit == BITS32) {
			sprintf(temp_string, "#%02x%02x%02x", cc->cc.cc24[cc->size - count].c.rouge,
			        cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
		}
		if (cc->compte_bit == BITS24) {
			sprintf(temp_string, "#%02x%02x%02x", cc->cc.cc32[cc->size - count].c.rouge,
			        cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
		}
		colors[count] = malloc(10 * sizeof(char)),
				strcpy(colors[count], temp_string);
	}
}

int send_receive_color(int socketfd) {

	char* path = calloc(256, sizeof(char));

	printf("Please enter the full path to the image (256 characters max):");
	scanf("%s", path);

	char* data = calloc(DATA_LENGTH, sizeof(char));

	int nb_colors_to_send = -1;
	while (nb_colors_to_send < 0 || nb_colors_to_send > 30) {
		printf("In how many colors, image needs to be resumed ? (1 < X < 30) X=");
		scanf("%d", &nb_colors_to_send);
	}


	char** colors = malloc(sizeof(char*) * nb_colors_to_send);
	analyse(path, colors, nb_colors_to_send);


	json_data json = json_create(nb_colors_to_send);
	strcpy(json.code, CODE_COLOR);
	for (int i = 0; i < nb_colors_to_send; ++i) {
		value v = value_create();
		strcpy(v.type, TYPE_STR);
		v.data = malloc(sizeof(char) * strlen(colors[i]));
		strcpy(v.data, colors[i]);
		json.values[i] = v;
	}

	char* serialized_json = serialize(&json);
	if (serialized_json == NULL) {
		fprintf(stderr, "error in client.color json");
		return -3;
	}
	strcpy(data, serialized_json);
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

	deserialize(&json, data);
	code code1 = getCode(json.code);
	if (code1 == COLOR) {
		if (json.data_length == 1) {
			printf("Response from server (color): %s\n", (string) json.values[0].data);
			fflush(stdout);
		} else {
			fprintf(stderr, "Error nb arguments in color response");
		}
	} else if (code1 == ERROR) {
		if (json.data_length == 1) {
			printf("Error from server: %s\n", (string) json.values[0].data);
		} else {
			fprintf(stderr, "Error nb arguments in color error: 1 needed");
		}
	} else {
		fprintf(stderr, "Wrong code in color response: %s", json.code);
	}

	free(colors);
	free(data);

	return 0;
}

int send_receive_name(int socketfd) {

	char* data = calloc(DATA_LENGTH, sizeof(char));

	char* message = malloc(MESSAGE_MAX_LENGH - 1);

	gethostname(message, MESSAGE_MAX_LENGH - 1);

	json_data json = json_create(1);
	strcpy(json.code, CODE_NAME);
	value v = value_create();
	strcpy(v.type, TYPE_STR);
	v.data = malloc(sizeof(char) * strlen(message));
	strcpy(v.data, message);
	free(message);
	json.values[0] = v;

	strcpy(data, serialize(&json));

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

	deserialize(&json, data);
	if (getCode(json.code) == NAME) {
		if (json.data_length == 1) {
			printf("Recieved name from server: %s\n", (string) json.values[0].data);
			fflush(stdout);
		} else {
			fprintf(stderr, "Error nb arguments in name response");
		}
	} else {
		fprintf(stderr, "Wrong code in name response:  %s %s", json.code, (string) json.values[0].data);
	}

	free(data);
	return 0;
}