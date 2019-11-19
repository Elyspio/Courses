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

string slice(char* src, int from, int to) {
    string str = malloc(strlen(src) - to - from);
	strncpy(str, src + from, to - from);
	return str;
}



string remove_all(const char *src, const char *chars) {

    int nb_chars_to_remove = 0;
    for(char c = src[0]; c != '\0'; c++) {
        for(char c_searched = chars[0]; c_searched != '\0'; c_searched ++) {
            if(c == c_searched) {
                nb_chars_to_remove++;
            }
        }
    }

    string str = calloc(nb_chars_to_remove, sizeof(char));
    int index_in_str = 0;
    for (int i = 0; src[i] != '\0'; ++i) {
        for (int j = 0; chars[j] != '\0'; ++j) {
            // foreach char in chars
            if (src[i] != chars[j]) {
                str[index_in_str] = src[i];
                index_in_str++;
            }
        }
    }

    return str;
}


string format_time() {
	string str = calloc(6, sizeof(char));
    time_t raw_time;
	struct tm* times;

	time(&raw_time);
	times = localtime(&raw_time);
	sprintf(str, "%02d:%02d:%02d", times->tm_hour, times->tm_min, times->tm_sec);
    return str;
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
	string alias = str;
	bool got_point = false;
	bool got_number_after_point = false;
	for (; *alias != '\0'; alias++) {
		if (*alias == '.') {
			got_point = true;
		}
		if (got_point) {
			if (*alias > '0' && *alias <= '9') {
				got_number_after_point = true;
			}
		}
	}


	return got_number_after_point;
}
