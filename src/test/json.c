//
// Created by elyspio on 28/09/2019.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "json.h"
#include "const.h"
#include "tools.h"


void remove_whitespace(char* str) {
	const char* d = str, * start = str;
	bool in_string = false;
	*str++ = *d++;
	do {
		if (*d == '\"' && !(d != start && *(d - 1) == '\\'))
			in_string = !in_string;
		if (in_string)
			continue;

		while (*d == ' ' || *d == '\n' || *d == '\t') {
			d++;
			if (*d == '\"')    // avoid skipping a \" after a whitespace
				in_string = !in_string;
		}

		*str++ = *d++;
	} while (*str);
}


string serialize(json_data* json) {
	string str = calloc(DATA_LENGTH, sizeof(char));
	char* code = malloc(30 * sizeof(char));
	strcpy(code, "{\"code\":\"");
	strcat(code, json->code);
	strcat(code, "\",\"values\":[");
	strcpy(str, code);

	for (int i = 0; i < json->data_length; ++i) {
		value current = json->values[i];
		if (strcmp(current.type, TYPE_BOOL) == 0) {
			strcat(str, (char*) current.data);
		} else if (strcmp(current.type, TYPE_INT) == 0) {
			sprintf(str, "%s%d", str, *(int*) current.data);
		} else if (strcmp(current.type, TYPE_DOUBLE) == 0) {
			sprintf(str, "%s%lf", str, *(double*) current.data);
		} else if (strcmp(current.type, TYPE_FLOAT) == 0) {
			sprintf(str, "%s%f", str, *(float*) current.data);
		} else if (strcmp(current.type, TYPE_STR) == 0) {
			sprintf(str, "%s\"%s\"", str, (char*) current.data);
		}

		if (i < json->data_length - 1) {
			strcat(str, ",");
		}
	}

	strcat(str, "]}");
	return str;
}


json_data empty_data() {
	json_data data;
	data.data_length = 0;
	return data;
}

///**
// * @brief Serializes a json_data to a string in json format
// */
//char* serialize(json_data* json) {
//	char* str = calloc(DATA_LENGTH, sizeof(char));
//	if (str == 0) {
//		perror("Could not allocate memory");
//		exit(1);
//	}
//
//	strcpy(str, "{\"code\": \"");
//	strcat(str, json->code);
//	strcat(str, "\", \"values\": [");
//
//	for (int i = 0; i < json->data_length; i++) {
//		strcat(str, "\"");
//
//		char* escaped_str = calloc(DATA_LENGTH, sizeof(char));
//		escape_str(escaped_str, json->values[i]);
//
//		strcat(str, escaped_str);
//		strcat(str, "\"");
//
//		if (i < json->data_length - 1)
//			strcat(str, ", ");
//	}
//
//	strcat(str, "]}");
//
//	return str;
//}

/**
 *
 * @param out
 * @param json
 * @return
 */
int deserialise(json_data* out, string json) {
	remove_whitespace(json);

	string start = "{\"code\":\"";
	size_t start_length = strlen(start);

	if (strncmp(json, start, start_length) != 0) {
		fprintf(stderr, "Error in json:\n %s \nDoes not start by %s", json, start);
	}

	string current = json + start_length;

	
	return true;
}

/**
 *
 * @param code
 * @return the code if one correspond to
 */
bool test_code(string code) {
	return
		(strcmp(code, CODE_NAME) == 0)    ||
		(strcmp(code, CODE_COLOR) == 0)   ||
		(strcmp(code, CODE_ERROR) == 0)   ||
		(strcmp(code, CODE_MESSAGE) == 0) ||
		(strcpy(code, CODE_CALCUL) == 0);
}


///**
// *
// * @param jsonData
// * @param str
// * @return -1 if json is malformed, 0 if process is successful
// */
//int deserialize(json_data* jsonData, char* str) {
//	remove_whitespace(str);
//
//	char* code_key = "{\"code\":\"";
//	size_t code_key_length = strlen(code_key);
//
//	if (strlen(str) < code_key_length) {
//		return -1;
//	}
//
//	if (strncmp(str, code_key, code_key_length) == 0) {
//		str += code_key_length;
//		char* code = malloc(DATA_LENGTH * sizeof(char));
//		int escaped_size = unescape_str(code, str);
//		jsonData->code = code;
//
//		str += escaped_size;
//
//		char* data_key = "\",\"values\":[";
//		size_t data_key_length = strlen(data_key);
//
//		if (strncmp(str, data_key, data_key_length) == 0) {
//			str += data_key_length;
//
//			jsonData->values = malloc(64 * sizeof(char*));
//			int data_length = 0;
//			while (*str) {
//				//printf("AAA:%d, %c ; ", data_length, *str);
//				if (*str == ']')
//					break;
//				if (*str == ',') {
//					str++;
//					continue;
//				}
//				if (*str == '\"') {
//					char* data = malloc(DATA_LENGTH * sizeof(char));
//					str += 1;
//					escaped_size = unescape_str(data, str);
//					jsonData->values[data_length] = data;
//					data_length++;
//					str += escaped_size + 1;
//				}
//			}
//			jsonData->data_length = data_length;
//		}
//	} else {
//		return -1;
//	}
//	return 0;
//}

enum objectState {
	STATE_NAME,
	STATE_VALUE
};


bool verify(string json_str) {
	const size_t json_len = strlen(json_str);

	// Cas ou le json ne commence pas par { ou [
	if ((json_str[0] != '{' && json_str[json_len - 1] != '}') &&
	    (json_str[0] != '[' && json_str[json_len - 1] != ']')) {
		fprintf(stderr, "Make sur that first and last characters are '{' '}' or '[' ']'");
		return false;
	}

	stack stack;
	stack.length = 0;
	char previous = 0;

	bool already_got_point = false;

	for (int i = 0; i < json_len; i++) {
		char current = json_str[i];

		if (stack.length == 0) {
			if (current == '{' || current == '[') {
				stack_push(&stack, current);
			} else {
				return false;
			}
		} else {
			char stack_top = stack_seek(&stack);
			switch (stack_top) {
				case '[': {
					if (is_number(previous)) {
						if (current == '.') {
							if (already_got_point) {
								return false;
							}
							already_got_point = true;
						}
					}
					if (current != '"' && !is_number(current)) {
						return false;
					}
				}

				case '{' : {

				}

				case '"': {

				}
			}

		}
		previous = current;


	}


	// gestion de la pile: [ { "



	return true;
	return false;
}


bool is_number(char c) {
	return c >= '0' && c <= '9';
}


/**
 * Try to parse a boolean or null
 * @param str the string to evaluate
 * @returns false if the string correspond to none of the following
 * @returns 1 if the string correspond to null
 * @returns 2 if the string correspond to true
 * @returns 3 if the string correspond to false
 */

int try_parse_other(char* str) {
	size_t str_len = strlen(str);
	char* true_str = "true";
	char* false_str = "false";
	char* null_str = "null";

	size_t i = strlen(null_str);
	if (i <= str_len && strcmp(str, null_str) == 0) return i;
	size_t i1 = strlen(true_str);
	if (i1 <= str_len && strcmp(str, true_str) == 0) return i1;
	size_t i2 = strlen(false_str);
	if (i2 <= str_len && strcmp(str, false_str) == 0) return i2;

	return false;

}

/**
 *
 * @param str the string to evaluate
 * @returns false if str is not a number or
 * @returns length (in char) of the number
 */
int try_parse_number(char* str) {
	size_t str_len = strlen(str);
	char current, previous = '\0';
	bool already_got_point = false;
	bool already_got_e = false;
	for (int i = 0; i < str_len; ++i) {
		current = str[i];
		//  todo to parent : verif plus ou moins inutile
		if (i == 0 && (!is_number(current) && current != '-')) {
			break;
		}


		if (previous == 'e' || previous == 'E') {

			if (!is_number(current) && current != '-' && current != '+') {
				break;
			} else {
				previous = current;
				continue;
			}
		}

		if (i == 1 && previous == '0') {
			if (is_number(current)) {
				break;
			}
			if (current != '.' && current != 'e' && current != 'E') {
				return i;
			}
		}

		if (i == 0 && current == '-') {
			previous = current;
			continue;
		}

		if (current == '.') {
			if (already_got_point || already_got_e) {
				break;
			} else {
				already_got_point = true;
				previous = current;
				continue;
			}
		}

		if (current == 'e' || current == 'E') {
			if (previous == '.') {
				break;
			}
			if (already_got_e) {
				break;
			} else {
				already_got_e = true;
				previous = current;
				continue;
			}
		}

		if (i > 0 && current == '-' && previous != 'e' && previous != 'E') {
			break;
		}

		if (!is_number(current)) {
			if (!is_number(previous)) {
				break;
			}
			return i;
		}
		previous = current;


	}

	return false;

}

/**
 *
 * @param str the string to evaluate and must start at the '"'
 * @returns false if str is not a number or
 * @returns length (in char) of the number
 */
int try_parse_str(char* str) {
	size_t str_len = strlen(str);
	stack stack = empty_stack();
	char current, previous = '\0';
	char allowedAfterBackSlash[9] = {'"', '\'', '/', '\\', 'b', 'f', 'n', 'r', 't'};

	for (int i = 0; i < str_len; ++i) {
		current = str[i];
		if (previous == '\\') {
			bool correct = false;
			for (int j = 0; j < 9; ++j) {
				if (allowedAfterBackSlash[j] == current) {
					correct = true;
				}
			}
			if (correct == false) { break; }
		} else {
			if (current == '\"') {
				if (i == 0 && stack.length == 0) {
					// debut du string
					stack_push(&stack, current);
				}
					// fin du string
				else if (stack_seek(&stack) == '\"') {
					stack_pop(&stack);
					return i + 1;
				} else {
					return 0;
				}
			}
		}
		previous = current;

	}


	return false;
}

/**
 *
 * @param str the string to evaluate and must start at the '['
 * @returns false if str is not a number or
 * @returns length (in char) of the array: where is array ends
 */
int try_parse_array(char* str) {
	size_t str_len = strlen(str);
	stack stack = empty_stack();
	char current;
	bool firstObject = true;

	for (int i = 0; i < str_len; ++i) {
		current = str[i];

		if (current == '[') {
			if (i == 0 && stack.length == 0) {
				stack_push(&stack, current);
			} else {
				try_parse_object(str + i);
			}
		} else {
			i += try_parse_whitespace(str + i);
			if (firstObject && str[i] == ']' && stack_seek(&stack) == '[')
				return i + 1;

			int len = try_parse_everything(str + i);
			if (len == 0) {
				return false;
			} else {
				i += len;
			}
			i += try_parse_whitespace(str + i);

			current = str[i];
			if (current == ',') {
				firstObject = false;
			} else if (current == ']' && stack_seek(&stack) == '[') {
				return i + 1;
			} else {
				return false;
			}
		}
	}

	return false;
}

int try_parse_object(char* str) {
	size_t str_len = strlen(str);
	stack stack = empty_stack();
	char current;
	bool firstObject = true;
	enum objectState currentState = STATE_NAME;

	for (int i = 0; i < str_len; ++i) {
		current = str[i];

		if (current == '{') {
			if (i == 0 && stack.length == 0) {
				stack_push(&stack, current);
				currentState = STATE_NAME;
			} else {
				try_parse_object(str + i);
			}
		} else if (currentState == STATE_NAME) {
			i += try_parse_whitespace(str + i);
			current = str[i];

			if (firstObject && current == '}' && stack_seek(&stack) == '{')
				return i + 1;
			if (current == '\"') {
				i += try_parse_str(str + i);
			} else {
				return false;
			}
			i += try_parse_whitespace(str + i);
			if (str[i] != ':') {
				return false;
			} else {
				currentState = STATE_VALUE;
			}
		} else {
			i += try_parse_whitespace(str + i);
			int len = try_parse_everything(str + i);
			if (len == 0) {
				return false;
			} else {
				i += len;
			}
			i += try_parse_whitespace(str + i);

			current = str[i];
			if (current == ',') {
				currentState = STATE_NAME;
				firstObject = false;
			} else if (current == '}' && stack_seek(&stack) == '{') {
				return i + 1;
			} else {
				return false;
			}
		}
	}

	return false;
}

int try_parse_whitespace(char* str) {
	size_t str_len = strlen(str);
	char current;

	for (int i = 0; i < str_len; i++) {
		current = str[i];
		if (current == ' ' || current == '\n' || current == '\r' || current == '\t')
			continue;
		else
			return i;
	}
	return str_len;
}

int try_parse_everything(char* str) {
	if (str[0] == '\"')
		return try_parse_str(str);
	if (str[0] == '[')
		return try_parse_array(str);
	if (str[0] == '{')
		return try_parse_object(str);
	if (is_number(str[0]) || str[0] == '-')
		return try_parse_number(str);
	if (str[0] == 't' || str[0] == 'f' || str[0] == 'n')
		return try_parse_other(str);

	return false;
}

