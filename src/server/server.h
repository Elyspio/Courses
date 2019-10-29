//
// Created by elyspio on 28/09/2019.
//

#include "../common/json.h"

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

int _handle_message(int socket_fd, json_data* json);

int _handle_calcul(int socket_fd, json_data* json);

int _handle_color(int socket_fd, json_data* json);

int _handle_name(int socket_fd, json_data* json);

int _handle_error(int socket_fd, char *message);

int _response(int client_socket_fd, char *message);

int listen_client();

int handle_request(int socket_fd);

#endif //PROJECT_SERVER_H
