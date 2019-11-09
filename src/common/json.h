//
// Created by elyspio on 28/09/2019.
//

#include "types.h"


#ifndef SRC_JSON_H
#define SRC_JSON_H

typedef struct json_data {
	string code;
	value* values;
	int data_length;
} json_data;

char* serialize(json_data* json);

void json_create_ptr(json_data* data, int nb_values);

json_data json_create(int nb_values);

void json_free(json_data* json);

int deserialize(json_data* jsonData, char* str);

bool is_number(char c);

bool test_code(string code);

int try_parse_other(char* str);

int try_parse_number(char* str);

int try_parse_str(char* str);

int try_parse_array(char* str);

int try_parse_object(char* str);

int try_parse_whitespace(char* str);

int try_parse_everything(char* str);

void json_print(json_data* json);


#endif //SRC_JSON_H
