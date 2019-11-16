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
#include <fcntl.h>

#include "server.h"
#include "../common/json.h"
#include "../common/enum.h"
#include "../common/tools.h"



int _response(int client_socket_fd, char *message) {
    int data_size = write(client_socket_fd, (void *) message, strlen(message));
    free(message);
    if (data_size < 0) {
        perror("erreur ecriture");
        return -1;
    }
    return 0;
}


int main() {


    string formatTime = format_time();
    printf("Server started at %s\n", formatTime);
    free(formatTime);

    int client_socket_fd = listen_client();
    if (client_socket_fd > 0) {

        while (true) {
            handle_request(client_socket_fd);
        }

    }


    return 0;
}


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
    server_addr.sin_port = htons(SERVER_PORT);
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
    int client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, (socklen_t * ) & client_addr_len);
    if (client_socket_fd < 0) {
        perror("Error: Accept");
        return -3;
    }

    string formatTime = format_time();
    printf("Client connected at %s\n", formatTime);
    free(formatTime);
    return client_socket_fd;
}


int handle_request(int socket_fd) {

    char *data = calloc(DATA_LENGTH, sizeof(char));

    do {
        int data_size = read(socket_fd, (void *) data, DATA_LENGTH);

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
            error_code = _handle_compute(socket_fd, &json);
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

int _handle_error(int socket_fd, char *message) {
    json_data json = json_create(1);
    strcpy(json.code, CODE_ERROR);
    json.values[0] = value_create();
    json.values[0].data = malloc(strlen(message) * sizeof(char));
    strcpy(json.values[0].data, message);
    strcpy(json.values[0].type, TYPE_STR);

    message = serialize(&json);

    char *data = calloc(DATA_LENGTH, sizeof(char));
    strcpy(data, message);
    return _response(socket_fd, data);
}

int _handle_message(int socket_fd, json_data *json) {

    if (json->data_length == 1) {
        printf("Message recieved from client: %s\n", (string) json->values[0].data);
        int prompt_length = strlen(CODE_MESSAGE);

        printf("Please enter the response: ");
        char *response_message = calloc(DATA_LENGTH - prompt_length, sizeof(char));
        scanf("%s", response_message); //		response_message[strlen(response_message) - 1] = '\0';

        json_free(json);
        json_data response_json = json_create(1);
        strcpy(response_json.code, CODE_MESSAGE);
        response_json.values[0] = value_create();
        response_json.values[0].data = calloc(strlen(response_message), sizeof(char));
        strcpy(response_json.values[0].type, TYPE_STR);

        strncpy(response_json.values[0].data, response_message, strlen(response_message));

        string data = serialize(&response_json);
        json_free(&response_json);

        return _response(socket_fd, data);
    }

    return _handle_error(socket_fd, "to handle a message, we need only 1 argument: message");


}


int _handle_compute(int socket_fd, json_data *json) {
    if (json->data_length >= 3) {

        if (strcmp(json->values[1].type, TYPE_INT) != 0 && strcmp(json->values[1].type, TYPE_DOUBLE) != 0) {
            fprintf(stderr, "Type error in _handle_compute, %s recieved when %s or %s were expected.",
                    json->values[1].type, TYPE_INT, TYPE_DOUBLE);
        }
        if (strcmp(json->values[2].type, TYPE_INT) != 0 && strcmp(json->values[2].type, TYPE_DOUBLE) != 0) {
            fprintf(stderr, "Type error in _handle_compute, %s recieved when %s or %s.", (string) json->values[2].type,
                    TYPE_INT,
                    TYPE_DOUBLE);
        }

        int nb_vars = json->data_length - 1;

        double *vars = calloc(nb_vars, sizeof(double));


        for (int i = 1; i < json->data_length; ++i) {
            if (strcmp(json->values[i].type, TYPE_DOUBLE) == 0) {
                vars[i - 1] = *(double *) json->values[i].data;
            } else if (strcmp(json->values[i].type, TYPE_INT) == 0) {
                vars[i - 1] = *(int *) json->values[i].data;
            } else {
                char error[100];
                sprintf(error, "Wrong type for number %d %s", i, json->values[i].type);
                return _handle_error(socket_fd, error);
            }

        }

        char operator = *((char *) json->values[0].data);
        double result = vars[0];
        char error_str[100];
        switch (operator) {
            case COMPUTE_OPERATOR_ADD:
                for (int i = 1; i < nb_vars; ++i) {
                    result += vars[i];
                }
                break;
            case COMPUTE_OPERATOR_SUB:
                for (int i = 1; i < nb_vars; ++i) {
                    result -= vars[i];
                }
                break;
            case COMPUTE_OPERATOR_DIV:
                for (int i = 1; i < nb_vars; ++i) {
                    result /= vars[i];
                }
                break;
            case COMPUTE_OPERATOR_MUL:
                for (int i = 1; i < nb_vars; ++i) {
                    result *= vars[i];
                }
                break;

            default:

                if (strcmp(json->values[0].data, COMPUTE_OPERATOR_MIN) == 0) {
                    double min = vars[0];
                    for (int i = 1; i < nb_vars; ++i) {
                        if (vars[i] < min) {
                            min = vars[i];
                        }
                    }
                    result = min;
                } else if (strcmp(json->values[0].data, COMPUTE_OPERATOR_MAX) == 0) {
                    double max = vars[0];
                    for (int i = 1; i < nb_vars; ++i) {
                        if (vars[i] > max) {
                            max = vars[i];
                        }
                    }
                    result = max;
                } else if (strcmp(json->values[0].data, COMPUTE_OPERATOR_AVG) == 0) {
                    result = _get_avg(vars, nb_vars);

                } else if (strcmp(json->values[0].data, COMPUTE_OPERATOR_SD) == 0) {
                    double avg = _get_avg(vars, nb_vars);
                    double sd = 0;
                    for (int i = 0; i < nb_vars; ++i) {
                        sd += (avg - vars[0]) * (avg - vars[0]);
                    }
                    result = sd / nb_vars;
                } else {
                    sprintf(error_str, "Unknown operator '%s' could not continue", (string) json->values[0].data);
                    return _handle_error(socket_fd, error_str);

                }
        }
        json_free(json);

        json_data response_json = json_create(1);
        strcpy(response_json.code, CODE_COMPUTE);
        response_json.values[0] = value_create();
        string result_str = malloc(DATA_LENGTH * sizeof(char));
        sprintf(result_str, "%lf", result);
        if (is_double(result_str)) {
            strcpy(response_json.values[0].type, TYPE_DOUBLE);
            *(double *) response_json.values[0].data = result;
        } else {

            strcpy(response_json.values[0].type, TYPE_INT);
            *(int *) response_json.values[0].data = (int) result;
        }

        char *data = calloc(DATA_LENGTH, sizeof(char));
        strcpy(data, serialize(&response_json));
        json_free(&response_json);
        return _response(socket_fd, data);
    }

    return
            _handle_error(socket_fd,
                          "to handle a calcul, we need 3 argument: operator nbA, nbB");
}


double _get_avg(double *values, int nb_values) {
    double sum = values[0];
    for (int i = 1; i < nb_values; ++i) {
        sum += values[i];
    }
    return sum / nb_values;
}

/**
 * Print the graph
 * @param socket_fd
 * @param json
 */
void plot(int socket_fd, struct json_data *json) {

    //Extraire le compteur et les couleurs RGB


    FILE *p = popen("gnuplot -persist 2>/tmp/test", "w");
    int fd = open("/tmp/test", O_RDONLY);

    string str = calloc(100, sizeof(char));
    if (read(fd, str, 100) > 0) {
        // + 18 for "Error on ..." chars
        string error = calloc(100 + 18, sizeof(char));
        sprintf(error, "Error on gnuplot: %s", str);
        // ignore the warning "Gtk-Message"
        if (strncmp(str, "Gtk-Message", 11) != 0) {
            _handle_error(socket_fd, error);
        }
    } else {
        fprintf(p, "set xrange [-15:15]\n");
        fprintf(p, "set yrange [-15:15]\n");
        fprintf(p, "set style fill transparent solid 0.9 noborder\n");
        fprintf(p, "set title 'Top %d colors'\n", json->data_length);
        fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
        for (int i = 0; i < json->data_length; i++) {
            int divide = 360 / json->data_length;
            fprintf(p, "0 0 %d %d %d 0x%s\n", divide, (i - 1) * divide, i * divide,
                    (string) json->values[i].data + 1);
        }
        fprintf(p, "e\n");

    }
    close(fd);
    pclose(p);
}


/**
 *
 * @param socket_fd
 * @param json
 * @return
 */
int _handle_color(int socket_fd, json_data *json) {

    if (json->data_length >= 1) {
        plot(socket_fd, json);

        json_free(json);
        struct json_data response_json = json_create(1);
        strcpy(response_json.code, CODE_COLOR);
        response_json.values[0] = value_create();
        string message = "saved";
        strcpy(response_json.values[0].type, TYPE_STR);
        response_json.values[0].data = malloc(strlen(message) * sizeof(char));
        strcpy(response_json.values[0].data, message);
        return _response(socket_fd, serialize(&response_json));

    }
    return _handle_error(socket_fd, "to handle colors, we need at least two arguments: nbColors [#color1 #color2]");
}


int _handle_name(int socket_fd, json_data *json) {
    if (json->data_length == 1 && strcmp(json->values[0].type, TYPE_STR) == 0) {
        printf("Client's name: %s\n", (string) json->values[0].data);
        return _response(socket_fd, serialize(json));
    }
    return _handle_error(socket_fd, "to handle name, we need one argument: name");

}




