//
// Created by elyspio on 18/11/2019.
//

#include <glob.h>

#ifndef NEW_COURSES_TEST_H
#define NEW_COURSES_TEST_H

typedef struct maillon {
	struct maillon* next;
	void* value;
} maillon;

typedef struct file {
	maillon* head;
} file;

void insert(file* file, void* elem);

void* delete(file* file, size_t ind);

void print_file(file* file);

void test_all_codes(char* client_path, char* server_path);


int test_message(flux* client, flux* server);
int test_name(flux* client, flux* server);
int test_color(flux* client, flux* server);
int test_compute(flux* client, flux* server);

#endif //NEW_COURSES_TEST_H
