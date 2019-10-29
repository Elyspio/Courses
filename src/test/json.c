//
// Created by elyspio on 28/09/2019.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "json.h"
#include "const.h"
#include "tools.h"


void remove_whitespace(char *str) {
    const char *d = str, *start = str;
    bool in_string = false;
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

    } while (*str++ = *d++);
}


/**
 * @brief Serializes a json_data to a string in json format
 */
char *serialize(json_data *json) {
    char *str = calloc(DATA_LENGTH, sizeof(char));
    if (str == 0) {
        perror("Could not allocate memory");
        exit(1);
    }

    strcpy(str, "{\"code\": \"");
    strcat(str, json->code);
    strcat(str, "\", \"data\": [");

    for (int i = 0; i < json->data_length; i++) {
        strcat(str, "\"");

        char *escaped_str = calloc(DATA_LENGTH, sizeof(char));
        escape_str(escaped_str, json->data[i]);

        strcat(str, escaped_str);
        strcat(str, "\"");

        if (i < json->data_length - 1)
            strcat(str, ", ");
    }

    strcat(str, "]}");

    return str;
}

/**
 *
 * @param jsonData
 * @param str
 * @return -1 if json is malformed, 0 if process is successful
 */
int deserialize(json_data *jsonData, char *str) {
    remove_whitespace(str);

    char *code_key = "{\"code\":\"";
    int code_key_length = strlen(code_key);

    if (strlen(str) < code_key_length) {
        return -1;
    }

    if (strncmp(str, code_key, code_key_length) == 0) {
        str += code_key_length;
        char *code = malloc(DATA_LENGTH * sizeof(char));
        int escaped_size = unescape_str(code, str);
        jsonData->code = code;

        str += escaped_size;

        char *data_key = "\",\"data\":[";
        int data_key_length = strlen(data_key);

        if (strncmp(str, data_key, data_key_length) == 0) {
            str += data_key_length;

            jsonData->data = malloc(64 * sizeof(char *));
            int data_length = 0;
            while (*str) {
                //printf("AAA:%d, %c ; ", data_length, *str);
                if (*str == ']')
                    break;
                if (*str == ',') {
                    str++;
                    continue;
                }
                if (*str == '\"') {
                    char *data = malloc(DATA_LENGTH * sizeof(char));
                    str += 1;
                    escaped_size = unescape_str(data, str);
                    jsonData->data[data_length] = data;
                    data_length++;
                    str += escaped_size + 1;
                }
            }
            jsonData->data_length = data_length;
        }
    } else {
        return -1;
    }
    return 0;
}


enum whatImDoing {
    STRING,
    ARRAY,
    OBJECT,
    NUMBER,
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

int try_parse_other(char *str) {
    size_t str_len = strlen(str);
    char *true_str = "true";
    char *false_str = "false";
    char *null_str = "null";

    if (strlen(null_str) <= str_len && strcmp(str, null_str) == 0) return 1;
    if (strlen(true_str) <= str_len && strcmp(str, true_str) == 0) return 2;
    if (strlen(false_str) <= str_len && strcmp(str, false_str) == 0) return 3;

    return false;

}

/**
 *
 * @param str the string to evaluate
 * @returns false if str is not a number or
 * @returns length (in char) of the number
 */
int try_parse_number(char *str) {
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
int try_parse_str(char *str) {
    size_t str_len = strlen(str);
    stack stack = empty_stack();
    char current, previous = '\0';
    char allowedAfterBackSlash[8] = {'"', '\'', '/', 'b', 'f', 'n', 'r', 't'};

    for (int i = 0; i < str_len; ++i) {
        current = str[i];
        if (current >= ' ' && current <= '~') {

            if (previous == '\\') {
                bool correct = false;
                for (int j = 0; j < 8; ++j) {
                    if (allowedAfterBackSlash[j] == current) {
                        correct = true;
                    }
                }
                if (correct == false) { break; }
            } else {
                if (current == '"') {
                    // debut du string
                    if (stack.length == 0) {
                        stack_push(&stack, current);
                    }
                    // fin du string
                    else if (stack_seek(&stack) == '"') {
                        stack_pop(&stack);
                        return i + 1;
                    }
                }
            }
        } else {
            return i;
        }
        previous = current;

    }


    return false;
}

json_node deserialize_generic(char *str) {
    json_node data;

    remove_whitespace(str);

    bool in_string = false;
    bool is_key = true;
    char *current_string = calloc(DATA_LENGTH, sizeof(char));
    char **keys = malloc(10 * sizeof(char *));
    int current_depth = 0;

    do {
        if (*str == '\"') {
            if (in_string) // finished getting current string
            {
                if (is_key) {
                    keys[current_depth] = malloc(DATA_LENGTH * sizeof(char));
                    strcpy(keys[current_depth], current_string);
                    current_depth++;
                }

                memset(current_string, 0, DATA_LENGTH * sizeof(char)); // prepare current_string for next string
            }

            in_string = !in_string;
        }

        if (in_string) {
            unsigned long str_len = strlen(current_string);
            current_string[str_len] = *str;
            current_string[str_len] = '\0';

            continue;
        }

        if (*str == ':') {
            is_key = false;
        }
    } while (*str++);

    free(current_string);
    free(keys);

    return data;
}

