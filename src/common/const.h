//
// Créé par Jonathan Guichard
//

#ifndef PROJECT_CONST_H
#define PROJECT_CONST_H

// Codes (protocols for the app)
#define CODE_MESSAGE "message"
#define CODE_COLOR "color"
#define CODE_COMPUTE "compute"
#define CODE_NAME "name"
#define CODE_ERROR "error"
#define MAX_CODE_LENGTH 10

// Compute operators
#define COMPUTE_OPERATOR_ADD '+'
#define COMPUTE_OPERATOR_SUB '-'
#define COMPUTE_OPERATOR_DIV '/'
#define COMPUTE_OPERATOR_MUL '*'
#define COMPUTE_OPERATOR_AVG "avg"
#define COMPUTE_OPERATOR_MIN "min"
#define COMPUTE_OPERATOR_MAX "max"
#define COMPUTE_OPERATOR_SD  "sd"

// Types
#define TYPE_STR        "string"
#define TYPE_INT        "int"
#define TYPE_DOUBLE     "double"
#define TYPE_FLOAT      "float"
#define TYPE_BOOL       "bool"
#define MAX_TYPE_LENGTH 10

// Json
#define JSON_CODE_TEMPLATE_STR "{\"code\":\""
#define JSON_VALUE_TEMPLATE_STR "\",\"values\":["


// Other constants
#define SERVER_PORT 1337
#define DATA_LENGTH 1024
#define MESSAGE_MAX_LENGH (DATA_LENGTH / 4)
#define true (1==1)
#define false (!true)

#endif //PROJECT_CONST_H
