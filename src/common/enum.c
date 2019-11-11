//
// Créer par Jonathan Guichard
//
#include <string.h>

#include "enum.h"
#include "json.h"
#include "const.h"


code getCode(char* str) {

	code code = NOT_IDENTIFIED;
	if (strncmp(str, CODE_MESSAGE, strlen(CODE_MESSAGE)) == 0) {
		code = MESSAGE;
	}
	if (strncmp(str, CODE_COLOR, strlen(CODE_COLOR)) == 0) {
		code = COLOR;
	}
	if (strncmp(str, CODE_COMPUTE, strlen(CODE_COMPUTE)) == 0) {
		code = CALCUL;
	}
	if (strncmp(str, CODE_NAME, strlen(CODE_NAME)) == 0) {
		code = NAME;
	}
	if (strncmp(str, CODE_ERROR, strlen(CODE_ERROR)) == 0) {
		code = ERROR;
	}
	return code;


}


