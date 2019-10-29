//
// Created by elyspio on 21/10/2019.
//

#include "types.h"
#include "json.h"
#include "stdio.h"

int main(int argc, char **args) {

    string t1 = "1234,";

    string t2 = "9e.9]";
    string t3 = "8.2e+99]";

    string t4 = "1e234,";
    string t5 = "1.234,";

    string t6 = "1.23-4,";
    string t7 = "1e23e4,";

    string t8 = "-,";

    printf("t1 %s : %d\n", t1, try_parse_number(t1));
    printf("t2 %s : %d\n", t2, try_parse_number(t2));
    printf("t3 %s : %d\n", t3, try_parse_number(t3));
    printf("t4 %s : %d\n", t4, try_parse_number(t4));
    printf("t5 %s : %d\n", t5, try_parse_number(t5));
    printf("t6 %s : %d\n", t6, try_parse_number(t6));
    printf("t7 %s : %d\n", t7, try_parse_number(t7));
    printf("t8 %s : %d\n", t8, try_parse_number(t8));

}