//
// Created by elyspio on 28/09/2019.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

#include "../common/types.h"

/**
 * @return File descriptor of the server's socket
 * @return -1 if could not connect to the server
 * @return -2 if could not create the socket
 */
int connect_client();


/**
 * Send a custom message to the server, the server will replies
 * @param socketfd
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_message(int socketfd);

/**
 * Send a compute task to the server, the server will replies the result.
 * @Operations sum
 * @Operations substract
 * @Operations multiply
 * @Operations divide
 * @Operations average
 * @Operations min
 * @Operations max
 * @Operations standard deviation
 * @param socketfd the socket of the server
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 * @return -3 if the response code is not CODE_COMPUTE
 */
int send_receive_compute(int socketfd);

/**
 * Analyse an image and send the result to the server for display
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_color(int socketfd);

/**
 * Send the hostname of the machine to the server, the server will send back the same message.
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_name(int socketfd);

/**
 * Analyse an image by summarize it in N major colors.
 * @param pathname the path to the image to analyse
 * @param colors an array of string that will contains the result.
 * @param nb_colors in how many colors the image will be summarized
 */
void analyse(string pathname, string *colors, int nb_colors);

/**
 * Display on terminal all actions that client can do
 * @param socked_fd the fd of the server
 */
void disp_menu(int socked_fd);

#endif //PROJECT_CLIENT_H