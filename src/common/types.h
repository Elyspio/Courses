//
// Created by Jonathan Guichard on 22/10/2019.
//

#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H


typedef char bool;
typedef char *string;


// region Stack

typedef struct stack_char {
    char data[1000];
    short length;
} stack_char;


/**
 * Add an element to the stack_char
 * @param stack
 * @param elem
 * @return false if the stack was full.
 */
bool stack_push(stack_char *stack, char elem);

/**
 * Remove last element of the stack
 * @param stack
 * @return the last element of the stack or false if the stack was empty
 */
char stack_pop(stack_char *stack);

/**
 * Get the last element
 * @param stack
 * @return  the last element of the stack or false if the stack was empty
 */
char stack_seek(stack_char *stack);

/**
 * Create a stack object
 * @return the created stack
 */
stack_char stack_create();

// endregion stack_char

// region value

typedef struct value {
    string type;
    void *data;
} value;

/**
 * Create a value object
 * @return the created object
 * @alloc
 **/
value value_create();

// endregion value

#endif //PROJECT_TYPES_H
