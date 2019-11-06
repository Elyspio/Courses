//
// Created by elyspio on 29/09/2019.
//

#include <time.h>
#include "tools.h"
#include "string.h"
#include "stdio.h"

void replace_all(char* src, char target, char by) {
	for (int i = 0; src[i] != '\0'; i++) {
		if (src[i] == target) {
			src[i] = by;
		}
	}
}

void slice(char* src, int from, int to) {
	int src_length = strlen(src);
	if (to + 1 < src_length) {
		src[to + 1] = '\0';
	}
	int nb_char_moved;
	int nb_char_to_move = to - from;
	for (nb_char_moved = 0; nb_char_moved <= nb_char_to_move; nb_char_moved++) {
		src[nb_char_moved] = src[from + nb_char_moved];
	}
	src[nb_char_moved] = '\0';
}

void remove_all(char* src, const char* chars) {

	for (int i = 0; src[i] != '\0'; ++i) {
		for (int j = 0; j < chars[j] != '\0'; ++j) {
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
