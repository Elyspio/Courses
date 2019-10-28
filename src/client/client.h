//
// Created by elyspio on 28/09/2019.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

int connect_client();

int send_receive_message(int socketfd);

int send_receive_calcul(int socketfd);

int send_receive_color(int socketfd);

int send_receive_name(int socketfd);


#endif //PROJECT_CLIENT_H

/* envoi et reception de message
 */

