//
// Created by elyspio on 28/09/2019.
//

#include "types.h"


#ifndef SRC_JSON_H
#define SRC_JSON_H

typedef struct json_data {
	string code;
	value* values;
	int data_length;
} json_data;

/**
 * Transform a json_data object to his string representation
 * @param json
 * @return the string representation in json format
 * @alloc
 */
string serialize(json_data* json);

/**
 * Initialise a json_data object with nb_values value* allocated
 * @param data a json_data object
 * @param nb_values the number of value that will be allocated
 */
void json_create_ptr(json_data* data, int nb_values);

/**
 * Create a json_data object with nb_values value* allocated
 * @param nb_values the number of value(s) that will be allocated
 */
json_data json_create(int nb_values);

/**
 * Free all malloced data of a json_data object.
 * @param json
 */
void json_free(json_data* json);

/**
 * Fill a json_data* from his str representation.
 * @param out
 * @param json
 * @return -1 if the json pass has parameter is not correct
 * @return true if deserialize is done
 */
int deserialize(json_data* jsonData, char* str);

/**
 * Check if the char passed as parameter is the string representation of a number '0' '1' ...
 * @param c
 * @return
 */
bool is_number(char c);

/**
 *
 * @param code a string
 * @return true if the string is one of the authorized codes.
 */
bool test_code(string code);

/**
 * Try to parse a boolean or null
 * @param str the string to evaluate
 * @returns false if the string correspond to none of the following
 * @returns 1 if the string correspond to null
 * @returns 2 if the string correspond to true
 * @returns 3 if the string correspond to false
 */
int try_parse_other(string str);

/**
 * Check if a string is the string representation of a number
 * @param str the string to evaluate
 * @returns false if str is not the string representation of a number
 * @returns length (in char) of the number
 */
int try_parse_number(string str);

/**
 * Return the length of the first string in str
 * @param str the string to evaluate and must start at the '"'
 * @returns false if str is not the string representation of a string
 * @returns length (in char) of the number
 */
int try_parse_str(string str);

/**
 * Check if an string version of an array is correct
 * @param str the string to evaluate and must start at the '['
 * @returns false if str is not the string representation of an array
 * @returns length (in char) of the array: where is array ends
 */
int try_parse_array(string str);

/**
 * Check if an string version of a object is correct
 * @param str the string to evaluate and must start at the '['
 * @returns false if str is not the string representation of a object (error in json)
 * @returns length (in char) of the array: where is object ends
 */
int try_parse_object(string str);

/**
 * @returns the length of the following whitespacess
 */
int try_parse_whitespace(string str);

/**
 * Generic way to parse a string
 * @param str the string to evaluate
 * @returns the number of charactere handled
 */
int try_parse_everything(string str);

/**
 * Prints all values from a json_data object
 * @debug
 * @param json
 */
void json_print(json_data *json);


#endif //SRC_JSON_H
