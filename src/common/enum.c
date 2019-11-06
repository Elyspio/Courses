//
// Created by elyspio on 08/10/2019.
//
#include <string.h>

#include "enum.h"
#include "json.h"
#include "const.h"

code getCode(char* str) {

	code code = NOT_IDENTIFIED;
	if (strncmp(str, PROMPT_MESSAGE, strlen(PROMPT_MESSAGE)) == 0) {
		code = MESSAGE;
	}
	if (strncmp(str, PROMPT_COLOR, strlen(PROMPT_COLOR)) == 0) {
		code = COLOR;
	}
	if (strncmp(str, PROMPT_CALCUL, strlen(PROMPT_CALCUL)) == 0) {
		code = CALCUL;
	}
	if (strncmp(str, PROMPT_NAME, strlen(PROMPT_NAME)) == 0) {
		code = NAME;
	}
	return code;


}


