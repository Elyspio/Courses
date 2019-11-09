//
// Created by elyspio on 28/09/2019.
//

#ifndef PROJECT_CONST_H
#define PROJECT_CONST_H

#define CODE_MESSAGE "message"
#define CODE_COLOR "color"
#define CODE_CALCUL "compute"
#define CODE_NAME "name:"
#define CODE_ERROR "error"


#define MAX_CODE_LENGTH 10
#define DATA_LENGTH 1024
#define MESSAGE_MAX_LENGH (DATA_LENGTH / 4)


#define COMPUTE_OPERATOR_ADD '+'
#define COMPUTE_OPERATOR_SUB '-'
#define COMPUTE_OPERATOR_DIV '/'
#define COMPUTE_OPERATOR_MUL '*'
#define COMPUTE_OPERATOR_AVG "avg"
#define COMPUTE_OPERATOR_MIN "min"
#define COMPUTE_OPERATOR_MAX "max"
#define COMPUTE_OPERATOR_SD "sd"



#define PORT 1337

typedef char bool;

#define true (1==1)
#define false (!true)

#endif //PROJECT_CONST_H
