#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "../common/const.h"
#include "../common/enum.h"
#include "../common/json.h"
#include "couleur.h"
#include "bmp.h"

int main(int argc, char **argv) {
    int client_socket_fd = connect_client();


    disp_menu(client_socket_fd);

    close(client_socket_fd);
}


void disp_menu(int socked_id) {
    bool run  = true;
    while(run) {
        printf("\nWhat do you want to do ?\n");
        printf("\t0: Close the connection\n");
        printf("\t1: Send a message\n");
        printf("\t2: Send the machine's name\n");
        printf("\t3: Send a compute\n");
        printf("\t4: Analyse an image\n");
        int choice = -1;
        while (choice < 0 || choice > 5) {
            scanf("%d", &choice);
        }

        switch (choice)
        {
            case 0: run = false; break;
            case 1: send_receive_message(socked_id); break;
            case 2: send_receive_name(socked_id); break;
            case 3: send_receive_calcul(socked_id); break;
            case 4: send_receive_color(socked_id); break;
        }
    }
    
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

    char *data = calloc(DATA_LENGTH, sizeof(char));

    char message[MESSAGE_MAX_LENGH];
    printf("Your message (max %d characters): ", MESSAGE_MAX_LENGH);
    scanf("%s", message);

    json_data json = {
            PROMPT_MESSAGE,
            malloc(sizeof(char *)),
            1
    };

    json.data[0] = message;
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

    if (getCode(json.code) == MESSAGE) {
        if (json.data_length == 1) {
            printf("Recieved message from server: %s\n", json.data[0]);
        } else {
            perror("Error nb arguments in message response");
        }
    } else {
        char error[100];
        sprintf(error, "Wrong code in response to a message:  %s", json.code);
        perror(error);
    }

    free(data);

    return 0;
}

/**
 *
 * @param socketfd
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_calcul(int socketfd) {

    char *data = calloc(DATA_LENGTH, sizeof(char));

    json_data json = {
            PROMPT_CALCUL,
            malloc(3 * sizeof(char *)),
            3
    };

    json.data[0] = malloc(sizeof(char));
    json.data[1] = malloc(MESSAGE_MAX_LENGH / 2 * sizeof(char));
    json.data[2] = malloc(MESSAGE_MAX_LENGH / 2 * sizeof(char));

    printf("Send a compute: < + -  / * > <a> <b> ");
    scanf("%s%s%s", json.data[0], json.data[1], json.data[2]);

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
            printf("Result from server: %s\n", json.data[0]);
        } else {
            perror("Error nb arguments in compute response");
        }
    } else {
        char error[100];
        sprintf(error, "Wrong code in response to a message:  %s", json.code);
        perror(error);
    }

    free(data);

    return 0;
}


void analyse(char *pathname, char **colors, int nb_colors) {
    //compte de couleurs
    couleur_compteur *cc = analyse_bmp_image(pathname);

    char* temp_string = calloc(10, sizeof(char));

    //choisir 10 couleurs
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

/**
 * Analyse an image and send the result to the server
 * @return 0 if everything has worked corectly
 * @return -1 if could not write in socket
 * @return -2 if could not read from socket
 */
int send_receive_color(int socketfd ) {

    char* path = calloc(256 ,sizeof(char));

    printf("Please enter the full path to the image (256 characters max):");
    scanf("%s", path);

    char *data = calloc(DATA_LENGTH, sizeof(char));

    int nb_colors_to_send = -1;
    while (nb_colors_to_send < 0 || nb_colors_to_send > 30) {
        printf("In how many colors, image needs to be resumed ? (1 < X < 30) X=");
        scanf("%d", &nb_colors_to_send);
    }


    char **colors = malloc(sizeof(char *) * nb_colors_to_send);
    analyse(path, colors, nb_colors_to_send);
    json_data json = {
            PROMPT_COLOR,
            colors,
            nb_colors_to_send
    };

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
    if (getCode(json.code) == COLOR) {
        if (json.data_length == 1) {
            printf("Response from server (color): %s\n", json.data[0]);
        } else {
            perror("Error nb arguments in color response");
        }
    } else {
        char error[100];
        sprintf(error, "Wrong code in color response:  %s", json.code);
        perror(error);
    }

    free(colors);
    free(data);

    return 0;
}

int send_receive_name(int socketfd) {

    char *data = calloc(DATA_LENGTH, sizeof(char));

    char message[MESSAGE_MAX_LENGH];

    gethostname(message, MESSAGE_MAX_LENGH - 1);

    json_data json = {
            PROMPT_NAME,
            calloc(1, sizeof(char *)),
            1
    };
    json.data[0] = message;

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
            printf("Recieved name from server: %s\n", json.data[0]);
        } else {
            perror("Error nb arguments in name response");
        }
    } else {
        char error[100];
        sprintf(error, "Wrong code in name response:  %s", json.code);
        perror(error);
    }

    free(data);
    return 0;
}