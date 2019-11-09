//
// Created by elyspio on 21/10/2019.
//

#include "types.h"
#include "./json.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "const.h"

void try_parsing();

int main(int argc, char** args) {

//    try_parsing();



//
//	json_data json;
//	json.data_length = 0;
//	json.values = malloc(sizeof(value) * 4);
//	json.code = CODE_CALCUL;
//	value v1;
//	v1.data = malloc(sizeof(int));
//	*(int*) v1.data = 2;
//	v1.type = TYPE_INT;
//	json.values[0] = v1;
//
//	value v3;
//	v3.data = malloc(sizeof(double));
//	*(double *) v3.data = 2;
//	v3.type = TYPE_DOUBLE;
//	json.values[1] = v3;
//
//	value v4;
//	v4.data = "null";
//	v4.type = TYPE_BOOL;
//	json.values[3] = v4;
//	value v2;
//	v2.data = "toto";
//	v2.type = TYPE_STR;
//	json.values[2] = v2;
//	json.data_length = 4;
//
//	string string1 = serialize(&json);
//	printf("%s", "{\"code\":\"compute\",\"values\":[2,2.000000,\"toto\",null]}");
	json_data *data = malloc(sizeof(json_data));
	char* string = malloc(1024);
	strcpy(string,"{\"code\":\"compute\",\"values\":[2,2.000000,\"toto\",null]}");
	deserialize(data, string);

    json_print(data);


//    void ** voids = malloc(4 * sizeof(void*));
//    voids[0] = malloc(sizeof(int) * 10);
//    voids[1] = malloc(sizeof(char) * 250);
//    voids[2] = malloc(sizeof(double) * 5 );
//
//    ((int*) voids[0])[0] = 1;DATA_LENGTH
//    ((char*) voids[1])[0] = 'A';
//    ((double *) voids[2])[0] = 23.5;
//
//    printf("%d %c %lf", ((int*)voids[0])[0], ((char*)voids[1])[0], ((double*)voids[2])[0]);
//
//
//    void *arr = malloc(sizeof(int) * 15);
//    for (int i = 0; i < 10; ++i) {
//        ((int *) arr)[i] = i;
//    }
//
//    for (int j = 10; j < 15; ++j) {
//        ((char *) arr)[j] = (char) ('a' + j - 10);
//    }
//
//
//    for (int i = 0; i < 15; ++i) {
//        printf("%d\n", ((int*) arr)[i]);
//    }

}


void try_parsing() {
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

	string str2 = "\"9\\\"g\"";
	string str3 = "\"é\",aa";

	string str4 = "1\"1\",aa";
	string str5 = "{\"aze\": [\"toto\", -27], \"a\": \"t\"}";

	string str6 = "\"1.23-4,\"";
	string str7 = "\"1e23e4,\"";

	string str8 = "\"-,\"";

	printf("str1 %s : %d\n", str1, try_parse_everything(str1));
	printf("str2 %s : %d\n", str2, try_parse_everything(str2));
	printf("str3 %s : %d\n", str3, try_parse_everything(str3));
	printf("str4 %s : %d\n", str4, try_parse_everything(str4));
	printf("str5 %s : %d\n", str5, try_parse_object(str5));
	printf("str6 %s : %d\n", str6, try_parse_everything(str6));
	printf("str7 %s : %d\n", str7, try_parse_everything(str7));
	printf("str8 %s : %d\n", str8, try_parse_everything(str8));

	string str_true = "true";
	string str_false = "false";
	string str_null = "null";
	printf("str_true %s : %d\n", str_true, try_parse_other(str_true));
	printf("str_false %s : %d\n", str_false, try_parse_other(str_false));
	printf("str_null %s : %d\n", str_null, try_parse_other(str_null));

}
