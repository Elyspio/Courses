//
// Créé par Olivier Pautrat
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "json.h"
#include "const.h"
#include "tools.h"

/**
 * Remove all whitespace from a string, its MODIFING the string
 * @param str
 */
void remove_whitespace(char *str) {
	const char *d = str, *start = str;
	bool in_string = false;
	do {
		if (*d == '\"' && !(d != start && *(d - 1) == '\\'))
			in_string = !in_string;
		if (in_string) {
			*str++ = *d++;
			continue;
		}

		while (*d == ' ' || *d == '\n' || *d == '\t') {
			d++;
			if (*d == '\"')    // avoid skipping a \" after a whitespace
				in_string = !in_string;
		}

		*str++ = *d++;
	} while (*str);
}


string serialize(json_data *json) {
	string str = calloc(DATA_LENGTH, sizeof(char));

    string start = calloc(strlen(JSON_CODE_TEMPLATE_STR) + MAX_CODE_LENGTH + strlen(JSON_VALUE_TEMPLATE_STR), sizeof(char));

    strcpy(start, JSON_CODE_TEMPLATE_STR);
	strcat(start, json->code);
    strcat(start, JSON_VALUE_TEMPLATE_STR);
	strcpy(str, start);

	string current_str = malloc(DATA_LENGTH * sizeof(char));
	for (int i = 0; i < json->data_length; ++i) {
		value current = json->values[i];
		memset(current_str, 0, DATA_LENGTH);
		if (strcmp(current.type, TYPE_BOOL) == 0) {
			strcat(current_str, (string) current.data);
		} else if (strcmp(current.type, TYPE_INT) == 0) {
			sprintf(current_str, "%d", *(int *) current.data);
		} else if (strcmp(current.type, TYPE_DOUBLE) == 0) {
			sprintf(current_str, "%lf", *(double *) current.data);
		} else if (strcmp(current.type, TYPE_FLOAT) == 0) {
			sprintf(current_str, "%f", *(float *) current.data);
		} else if (strcmp(current.type, TYPE_STR) == 0) {
			sprintf(current_str, "\"%s\"", (string) current.data);
		}
		strcat(str, current_str);

		if (i < json->data_length - 1) {
			strcat(str, ",");
		}
	}

	strcat(str, "]}");

	if (try_parse_everything(str) != strlen(str)) {
		fprintf(stderr, "Error: json created is not correct : %s", str);

		return NULL;
	}

	return str;
}


json_data json_create(int nb_values) {
	json_data data;
	data.code = malloc(MAX_CODE_LENGTH * sizeof(char));
	data.data_length = nb_values;
	data.values = malloc(nb_values * sizeof(value));
	return data;
}

void json_create_ptr(json_data *data, int nb_values) {
	data->data_length = nb_values;
	data->code = calloc(MAX_CODE_LENGTH, sizeof(char));
	data->values = calloc(nb_values, sizeof(value));
}


void json_free(json_data *json) {
	for (int i = 0; i < json->data_length; ++i) {
		free(json->values[i].type);
		free(json->values[i].data);
	}
	free(json->code);
	free(json->values);
}



int deserialize(json_data *out, string json) {

	if (try_parse_everything(json) != strlen(json)) {
		fprintf(stderr, "Error: json read is not correct");
		return -1;
	}

	remove_whitespace(json);

	string start = malloc(1024);
	strcpy(start, "{\"code\":\"");
	size_t start_length = strlen(start);

	if (strncmp(json, start, start_length) != 0) {
		fprintf(stderr, "Error in json:\n %s \nDoes not start by %s", json, start);
		return false;
	}

	string current = json + start_length - 1;

	int code_length = try_parse_str(current) - 1;
	string copy = slice(current, 1, code_length);

	if (test_code(copy)) {
		out->code = malloc(sizeof(char) * (strlen(copy) + 1));
		strcpy(out->code, copy);
	} else {
		fprintf(stderr, "Error in json.code:\n %s \nUnknown code %s", json, copy);
		return false;
	}
	free(copy);

	current += code_length + 1;

	string value_name = calloc(1024, 1);
	strcpy(value_name, ",\"values\":[");
	if (strncmp(current, value_name, strlen(value_name)) != 0) {
		fprintf(stderr, "Error in json.value.key:\n %s \n %s", json, current);
		return false;
	}
	current += strlen(value_name);
	char *current_c = current;
	int nb_values = 0;

	char *value_str = calloc(DATA_LENGTH, sizeof(char));
	out->values = calloc(1024, sizeof(value));
	while (*current_c != ']') {
		nb_values++;

		value *v = calloc(sizeof(value), 1);
		memset(value_str, 0, DATA_LENGTH);
		v->data = malloc(sizeof(void *));
		v->type = malloc(64);

		int value_length = try_parse_number(current_c);

		if (value_length > 0) {
			strncpy(value_str, current_c, value_length);
			value_str[value_length] = '\0';
			bool isDouble = is_double(value_str);
			if (isDouble) {
				strcpy(v->type, TYPE_DOUBLE);
				*(double *) v->data = strtod(value_str, NULL);
			} else {
				strcpy(v->type, TYPE_INT);
				*(int *) v->data = (int) strtol(value_str, NULL, 10);
			}

		} else if ((value_length = try_parse_str(current_c)) > 0) {
			strncpy(value_str, current_c + 1, value_length - 2);
			value_str[value_length] = '\0';
			strcpy(v->type, TYPE_STR);

			strcpy(v->data, value_str);
		} else if ((value_length = try_parse_other(current_c)) > 0) {
			strncpy(value_str, current, value_length);
			value_str[value_length] = '\0';
			strcpy(v->type, TYPE_BOOL);

			if (strcmp(value_str, "null") == 0) {
				*(bool *) v->data = false;
			}
			if (strcmp(value_str, "false") == 0) {
				*(bool *) v->data = false;
			}
			if (strcmp(value_str, "true") == 0) {
				*(bool *) v->data = true;
			}

		} else {
			fprintf(stderr,
					"Error in json.code:\n %s \nThe type of value must be: number, string or boolean, found [%s]", json,
					current_c);
			return false;
		}

		// 1 + to skip ','
		current_c += value_length;
		if (*current_c == ',') current_c++;

		out->values[nb_values - 1] = *v;
	}

	out->data_length = nb_values;

	return true;
}



bool test_code(string code) {
	return
			(strncmp(code, CODE_NAME, strlen(CODE_NAME)) == 0) ||
			(strncmp(code, CODE_COLOR, strlen(CODE_COLOR)) == 0) ||
			(strncmp(code, CODE_ERROR, strlen(CODE_ERROR)) == 0) ||
			(strncmp(code, CODE_MESSAGE, strlen(CODE_MESSAGE)) == 0) ||
			(strncmp(code, CODE_COMPUTE, strlen(CODE_COMPUTE)) == 0);
}

enum objectState {
	STATE_NAME,
	STATE_VALUE
};


bool is_number(char c) {
	return c >= '0' && c <= '9';
}




int try_parse_other(char *str) {
    size_t str_len = strlen(str);
    char *true_str = "true";
    char *false_str = "false";
    char *null_str = "null";

    size_t i = strlen(null_str);
    if (i <= str_len && strncmp(str, null_str, i) == 0) return i;
    size_t i1 = strlen(true_str);
    if (i1 <= str_len && strncmp(str, true_str, i1) == 0) return i1;
    size_t i2 = strlen(false_str);
    if (i2 <= str_len && strncmp(str, false_str, i2) == 0) return i2;

    return false;

}


int try_parse_number(char *str) {
    size_t str_len = strlen(str);
    char current, previous = '\0';
    bool already_got_point = false;
    bool already_got_e = false;
    int i;
    for (i = 0; i < str_len; ++i) {
        current = str[i];
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
    if (i == str_len) {
        return i + 1;
    }

    return false;

}


int try_parse_str(char *str) {
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


int try_parse_array(char *str) {
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


int try_parse_object(char *str) {
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


int try_parse_whitespace(char *str) {
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


int try_parse_everything(char *str) {
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




void json_print(json_data *json) {
    printf("json.code = %s\n", json->code);
    for (int i = 0; i < json->data_length; ++i) {
        printf("\tjson.values[%d].type = %s\n", i, (string) json->values[i].type);
        if (strcmp(json->values[i].type, TYPE_STR) == 0) {
            printf("\tjson.values[%d].data = \"%s\"\n", i, (string) json->values[i].data);
        } else if (strcmp(json->values[i].type, TYPE_BOOL) == 0) {
            printf("\tjson.values[%d].data = %s\n", i, (string) json->values[i].data);
        } else if (strcmp(json->values[i].type, TYPE_DOUBLE) == 0) {
            printf("\tjson.values[%d].data = %lf\n", i, *(double *) json->values[i].data);
        } else if (strcmp(json->values[i].type, TYPE_INT) == 0) {
            printf("\tjson.values[%d].data = %d\n", i, *(int *) json->values[i].data);
        }
    }
}
