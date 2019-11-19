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


#endif //NEW_COURSES_TEST_H
