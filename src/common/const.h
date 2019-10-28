//
// Created by elyspio on 28/09/2019.
//

#ifndef PROJECT_CONST_H
#define PROJECT_CONST_H

#define PROMPT_MESSAGE "Message:"
#define PROMPT_COLOR "Color:"
#define PROMPT_CALCUL "Calcul:"
#define PROMPT_NAME "Name:"
#define PROMPT_ERROR "Error:"
typedef enum {
	MESSAGE,
	CALCUL,
	COLOR,
	NAME,
	NOT_IDENTIFIED
} code;
#define DATA_LENGTH 1024

#define PORT 1337

typedef char bool;

#define true (1==1)
#define false (!true)

#endif //PROJECT_CONST_H
