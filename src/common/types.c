//
// Created by Jonathan Guichard on 22/10/2019.
//

#include "types.h"
#include "const.h"
#include "stdlib.h"


bool stack_push(stack_char* stack, char elem) {
	if (stack->length <= 1000) {
		stack->length++;
		stack->data[stack->length - 1] = elem;
		return true;
	}
	return false;
}

char stack_pop(stack_char* stack) {
	if (stack->length > 0) {
		stack->length--;
		return stack_seek(stack);
	}
	return false;
}

char stack_seek(stack_char* stack) {
	if (stack->length > 0) {
		return stack->data[stack->length - 1];
	}
	return false;
}

stack_char stack_create() {
	stack_char stack;
	stack.length = 0;
	return stack;
}

value value_create() {
	value v;
	v.type = malloc(sizeof(char) * MAX_TYPE_LENGTH);
	v.data = malloc(sizeof(void*));
	return v;
}

