//
// Created by elyspio on 22/10/2019.
//

#ifndef PROJECT_TYPES_H
#define PROJECT_TYPES_H


typedef char bool;
typedef char *string;


// region Stack

typedef struct stack {
    char data[1000];
    short length;
} stack;

bool stack_push(stack* stack , char elem);
char stack_pop(stack* stack);
char stack_seek(stack* stack);
stack empty_stack();

// endregion stack

#endif //PROJECT_TYPES_H
