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
string serialize2(json_data* json);
json_data empty_data();

int deserialize(json_data* jsonData, char* str);

bool verify(string json_str);

bool is_number(char c);

int try_parse_other(char* str);

int try_parse_number(char* str);

int try_parse_str(char* str);

int try_parse_array(char* str);

int try_parse_object(char* str);

int try_parse_whitespace(char* str);

int try_parse_everything(char* str);

#endif //SRC_JSON_H
