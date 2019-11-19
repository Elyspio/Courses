//
// Created by elyspio on 21/10/2019.
//


#include "../common/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/json.h"
#include "../common/tools.h"
#include "test.h"


file new_file();

int main(int argc, char **args) {
	file file = new_file();
	maillon  m;
	m.value = malloc(sizeof(int*));
	*(int*) m.value = 1;
	file.head = &m;

}


file new_file() {
	file f;
	f.head = NULL;
	return f;
}

void insert(file* file, void* elem) {

}

void* delete(file* file, size_t ind) {
	return NULL;
}

void print_file(file* file) {

}
