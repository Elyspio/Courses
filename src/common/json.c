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
char* serialize(json_data* json) {
	char* str = calloc(DATA_LENGTH, sizeof(char));
	if (str == 0) {
		perror("Could not allocate memory");
		exit(1);
	}

	strcpy(str, "{\"code\": \"");
	strcat(str, json->code);
	strcat(str, "\", \"data\": [");

	for (int i = 0; i < json->data_length; i++) {
		strcat(str, "\"");

		char* escaped_str = calloc(DATA_LENGTH, sizeof(char));
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
int deserialize(json_data* jsonData, char* str) {
	remove_whitespace(str);

	char* code_key = "{\"code\":\"";
	int code_key_length = strlen(code_key);

	if (strlen(str) < code_key_length) {
		return -1;
	}

	if (strncmp(str, code_key, code_key_length) == 0) {
		str += code_key_length;
		char* code = malloc(DATA_LENGTH * sizeof(char));
		int escaped_size = unescape_str(code, str);
		jsonData->code = code;

		str += escaped_size;

		char* data_key = "\",\"data\":[";
		int data_key_length = strlen(data_key);

		if (strncmp(str, data_key, data_key_length) == 0) {
			str += data_key_length;

			jsonData->data = malloc(64 * sizeof(char*));
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
					char* data = malloc(DATA_LENGTH * sizeof(char));
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

json_node deserialize_generic(char* str) {
	json_node data;

	remove_whitespace(str);

	bool in_string = false;
	bool is_key = true;
	char* current_string = calloc(DATA_LENGTH, sizeof(char));
	char** keys = malloc(10 * sizeof(char*));
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

