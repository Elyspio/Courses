//
// Created by elyspio on 28/09/2019.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

int connect_client();

int send_receive_message(int socketfd);

int send_receive_compute(int socketfd);

int send_receive_color(int socketfd);

int send_receive_name(int socketfd);

void analyse(char* pathname, char** colors, int nb_colors);

void disp_menu(int socked_id);

#endif //PROJECT_CLIENT_H