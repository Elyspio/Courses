//
// Created by elyspio on 21/10/2019.
//


#include "../common/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include <fcntl.h>
#include <bits/fcntl-linux.h>
#include "../common/json.h"
#include "../common/tools.h"
#include "test.h"


/**
 *
 * @param argc 3
 * @param args  [test.app, path_to_client, path_to_server]
 * @return
 */
int main(int argc, char** args) {
	if (argc == 3) {
		test_all_codes(args[1], args[2]);
	} else {
		test_all_codes("/media/windows/Progs/new_courses/dist/client.app",
		               "/media/windows/Progs/new_courses/dist/server.app");
	}
}


void test_all_codes(char* client_path, char* server_path) {

	flux server = popen_in_out(server_path);

	usleep(1000000);

	flux client = popen_in_out(client_path);

	bool status[4];

	status[0] = test_message(&client, &server);
//	status[1] = test_name(&client, &server);
//	status[2] = test_compute(&client, &server);
//	status[3] = test_color(&client, &server);


}


int test_message(flux* client, flux* server) {

	string str = malloc(2);
	sprintf(str, "%d", MENU_CHOICE_MESSAGE);
	string response = calloc(1024, sizeof(char));

	memset(response, 0, 1024);

	int writed = write(client->stdin, str, strlen(str));
	fsync(client->stdin);
	if (writed <= 0) {
		perror("Error write");
	}
	usleep(10000);


	string client_message = "aaa kk ";
	string server_message = "bbb ll";



	writed = write(client->stdin,  client_message, strlen(client_message));
	if (writed <= 0) {
		perror("Error wri2te");
	}

	usleep(1000000);

	read(server->stdout, response, 1024);

	if (strstr(response, client_message) == NULL) {
		fprintf(stderr, "Message received from client is not \"%s\" : \"%s\"", client_message, response);
		return false;
	}

	dprintf(server->stdin, "%s", server_message);
	usleep(1000000);
	memset(response, 0, 1024);
	read(client->stdout, response, 1024);

	if (strstr(response, server_message) == NULL) {
		fprintf(stderr, "Message received from server is not \"%s\" : \"%s\"", server_message, response);
		return false;
	}

	return true;
}


int test_name(flux* client, flux* server) {

	string hostname = calloc(1024, sizeof(char));
	gethostname(hostname, 1024);
	string response = calloc(1024, sizeof(char));

	dprintf(client->stdout, "%s", hostname);
	usleep(100000);
	read(server->stdin, response, 1024);

	if (strcmp(response, hostname) != 0) {
		fprintf(stderr, "Name received from client is not %s : %s", hostname, response);
		return false;
	}

	dprintf(server->stdout, "%s", hostname);
	usleep(100000);
	memset(response, 0, 1024);
	read(client->stdin, response, 1024);

	if (strcmp(response, hostname) != 0) {
		fprintf(stderr, "Name received from server is not %s : %s", hostname, response);
		return false;
	}

	return true;
}

int test_compute(flux* client, flux* server) {
	return true;
}

int test_color(flux* client, flux* server) {
	return true;
}
