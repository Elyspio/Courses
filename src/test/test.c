//
// Created by elyspio on 21/10/2019.
//


#include "../common/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/json.h"
#include "../common/tools.h"

int main(int argc, char **args) {
    string s = malloc(1024), s2 = malloc(1024);
    scanf("%s %[^\n]", s, s2);
    printf("%s,\n%s\n", s, s2);
    char delemiter[1] = " ";

    json_data json = json_create(1);

    char *ptr = strtok(s2, delemiter);
    int i = 1;
    while (ptr != NULL) {
        printf("%d | %s\n", i, ptr);
        if (try_parse_number(ptr) > 0) {
            json.data_length = i ;
            json.values[i - 1] = value_create();
            if (is_double(ptr)) {
                *(double *) json.values[i - 1].data = strtod(ptr, NULL);
                strcpy(json.values[i - 1].type, TYPE_DOUBLE);
            } else {
                printf("%s is a int\n",  ptr);
                *(int *) json.values[i - 1].data = (int) strtod(ptr, NULL);
                strcpy(json.values[i - 1].type, TYPE_INT);
            }
        }
        else {
            printf("%s is not a number", ptr);
        }
        i++;
        json.values = realloc(json.values, i * sizeof(value));
        ptr = strtok(NULL, delemiter);

    }
    strcpy(json.code, CODE_CALCUL);
    json_print(&json);
}
