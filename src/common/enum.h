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

/**
 * Get the code which his representation is str
 * @param str the string representation of the code
 */
code getCode(char* str);

#endif //CPROJECT_ENUM_H
