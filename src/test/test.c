//
// Created by elyspio on 21/10/2019.
//

#include "types.h"
#include "json.h"
#include "stdio.h"

int main(int argc, char **args) {

    string n1 = "1234,";

    string n2 = "9e.9]";
    string n3 = "8.2e+99]";

    string n4 = "1e234,";
    string n5 = "1.234,";

    string n6 = "1.23-4,";
    string n7 = "1e23e4,";

    string n8 = "-,";

    printf("n1 %s : %d\n", n1, try_parse_number(n1));
    printf("n2 %s : %d\n", n2, try_parse_number(n2));
    printf("n3 %s : %d\n", n3, try_parse_number(n3));
    printf("n4 %s : %d\n", n4, try_parse_number(n4));
    printf("n5 %s : %d\n", n5, try_parse_number(n5));
    printf("n6 %s : %d\n", n6, try_parse_number(n6));
    printf("n7 %s : %d\n", n7, try_parse_number(n7));
    printf("n8 %s : %d\n", n8, try_parse_number(n8));
    string str1 = "\"1234,\"";

    string str2 = "\"9\q\"";
    string str3 = "\"abc\"";

    string str4 = "\"1e234,\"";
    string str5 = "\"1.234,\"";

    string str6 = "\"1.23-4,\"";
    string str7 = "\"1e23e4,\"";

    string str8 = "\"-,\"";

    printf("str1 %s : %d\n", str1, try_parse_str(str1));
    printf("str2 %s : %d\n", str2, try_parse_str(str2));
    printf("str3 %s : %d\n", str3, try_parse_str(str3));
    printf("str4 %s : %d\n", str4, try_parse_str(str4));
    printf("str5 %s : %d\n", str5, try_parse_str(str5));
    printf("str6 %s : %d\n", str6, try_parse_str(str6));
    printf("str7 %s : %d\n", str7, try_parse_str(str7));
    printf("str8 %s : %d\n", str8, try_parse_str(str8));


    string str_true = "true";
    string str_false = "false";
    string str_null = "null";
    printf("str_true %s : %d\n", str_true, try_parse_other(str_true));
    printf("str_false %s : %d\n", str_false, try_parse_other(str_false));
    printf("str_null %s : %d\n", str_null, try_parse_other(str_null));


}