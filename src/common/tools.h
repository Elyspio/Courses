//
// Created by elyspio on 29/09/2019.
//

#ifndef PROJECT_TOOLS_H
#define PROJECT_TOOLS_H

#include "const.h"
#include "types.h"

void replace_all(char* src, char target, char by);

char* slice(char* src, int from, int to);

/**
 *
 * @param src
 * @param chars array of char to remove, MUST end by NULL
 */
void remove_all(char* src, const char* chars);

void format_time(char* dest);

void escape_str(char* dest, char* src);

int unescape_str(char* dest, char* src);

bool is_double(string str);

#endif //PROJECT_TOOLS_H
