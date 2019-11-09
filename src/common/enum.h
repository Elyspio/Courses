//
// Created by elyspio on 08/10/2019.
//


#ifndef CPROJECT_ENUM_H
#define CPROJECT_ENUM_H


typedef enum {
	MESSAGE,
	CALCUL,
	COLOR,
	NAME,
	NOT_IDENTIFIED,
	ERROR
} code;

code getCode(char* str);

#endif //CPROJECT_ENUM_H
