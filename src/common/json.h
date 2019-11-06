//
// Created by elyspio on 28/09/2019.
//


#ifndef SRC_JSON_H
#define SRC_JSON_H

typedef struct json_node {
	char* name;
	struct json_node* children;
	void* list;
	int list_length;
} json_node;


typedef struct json_data {
	char* code;
	char** data;
	int data_length;
} json_data;

char* serialize(json_data* json);

int deserialize(json_data* jsonData, char* str);

#endif //SRC_JSON_H
