//
// Created by elyspio on 29/09/2019.
//

#include <time.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "types.h"
#include "const.h"

void replace_all(char* src, char target, char by) {
	for (int i = 0; src[i] != '\0'; i++) {
		if (src[i] == target) {
			src[i] = by;
		}
	}
}

char* slice(char* src, int from, int to) {
	char* str = malloc(strlen(src));
	strncpy(str , src + from, to- from );
	return str;
}

void remove_all(char* src, const char* chars) {

	for (int i = 0; src[i] != '\0'; ++i) {
		for (int j = 0; chars[j] != '\0'; ++j) {
			// foreach char in chars
			if (src[i] == chars[j]) {
				// move chars
				for (int k = i; src[k + 1] != '\0'; ++k) {
					src[k] = src[k + 1];
				}
				src[strlen(src) - 1] = '\0';
			}
		}
	}
}


void format_time(char* dest) {
	time_t raw_time;
	struct tm* times;

	time(&raw_time);
	times = localtime(&raw_time);

	sprintf(dest, "%02d:%02d:%02d", times->tm_hour, times->tm_min, times->tm_sec);
}

void escape_str(char* dest, char* src) {
	*dest = 0;
	char* start = src;
	while (*src) {
		switch (*src) {
			case '\"':
				strcat(dest++, "\\\"");
				break;
			case '\\':
				strcat(dest++, "\\\\");
				break;
			default:
				*dest = *src;
		}
		src++;
		*++dest = 0;
	}
	src = start;
}


int unescape_str(char* dest, char* src) {
	int size = 0;
	while (*src != '\"') {
		if (*src == '\\' && *(src + 1)) {
			if (*(src + 1) == '\"' || *(src + 1) == '\\') {
				src++;
				size++;
			}
		}
		*dest++ = *src++;
		size++;
	}
	*(dest) = '\0';
	return size;
}


bool is_double(string str) {
	string alias =str;
	for(; *alias != '\0';  alias++) {
		if (*str  == '.') return true;
	}
	return false;
}