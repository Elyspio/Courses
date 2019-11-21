//
// Créé par Jonathan Guichard
//

#include "../common/json.h"

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

int _handle_message(int socket_fd, json_data* json);

/**
 * Do mathematical operations for the client and return the result to him
 * @param socket_fd
 * @param json
 * @return
 */
int _handle_compute(int socket_fd, json_data* json);

/**
 * Print the graph representation of colors on Server
 * @param socket_fd
 * @param json
 */
int _handle_color(int socket_fd, json_data* json);

/**
 * Send back the same data to the client
 * @param socket_fd
 * @param json
 * @return
 */
int _handle_name(int socket_fd, json_data* json);

/**
 * Function to handle all errors on server
 * @param socket_fd
 * @param message
 * @return
 */
int _handle_error(int socket_fd, string message);

/**
 *
 * @param client_socket_fd
 * @param message
 * @return 0 if everything has worked correctly
 * @return -1 if could not write data into the socket
 */
int _response(int client_socket_fd, string message);

/**
 * Get the average of an array of doubles
 * @param values an array
 * @param nb_values how many value in array
 * @return the mean of values
 */
double _get_avg(double* values, int nb_values);

/**
 * Wait a connection with a client
 * @return the socket of the connected client
 * @return -1 if could not open a socket
 * @return -2 if could not bind socket and the server
 * @return -3 if could not connect to a client
 *
 */
int listen_client();



/**
 * Create the connection with the client
 * @param socketfd
 * @returns client_fd
 * @fork
 */
int wait_client(int socketfd);

/**
 * Middleware to handle all requests
 * @param socket_fd
 * @return 0 if everything has worked correctly
 */
int handle_request(int socket_fd);

#endif //PROJECT_SERVER_H
