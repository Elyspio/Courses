//
// Created by elyspio on 29/09/2019.
//

#ifndef PROJECT_TOOLS_H
#define PROJECT_TOOLS_H

#include "const.h"
#include "types.h"

/**
 * Replace all char from a char to another char
 * @param src
 * @param target
 * @param by
 */
void replace_all(char* src, char target, char by);

/**
 * @returns a substring of src, have to be freed.
 * @param src initial string
 * @param from initial index
 * @param to last index
 * @alloc
 */
string slice(char* src, int from, int to);

/**
 *
 * @param src
 * @param chars to be removed
 * @return a new string without all char that are in chars
 * @alloc
 */
string remove_all(const char* src, const char* chars);

/**
 * @return the current time as a string hh:mm:ss
 * @alloc
 */
string format_time();

void escape_str(char* dest, char* src);

int unescape_str(char* dest, char* src);

bool is_double(string str);

#endif //PROJECT_TOOLS_H
