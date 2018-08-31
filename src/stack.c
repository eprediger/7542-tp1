#include "stack.h"

#include <stdio.h>

stack_t* stack_init() {
	stack_t* self = malloc(sizeof(stack_t));
	self->top = NULL;

	return self;
}

void stack_destroy(stack_t* self) {
	if (self != NULL) {
		while (self->top != NULL) {
			stack_pop(self);
		}

		free(self);
	}
}

void stack_push(stack_t* self, int val) {
	node_t* nodo = node_init(val);
	node_set_next(nodo, self->top);
	self->top = nodo;
}

int stack_pop(stack_t* self) {
	int popped_value = node_get_value(self->top);
	
	node_t* old_top = self->top;
	self->top = node_get_next(self->top);

	node_destroy(old_top);

	return popped_value;
}

int stack_get_top(stack_t* self) {
	return node_get_value(self->top);
}

void stack_print(stack_t* self) {
	printf("%s", "Stack: ");
	if (self != NULL) {
		node_t* temp = self->top;
		while (temp != NULL) {
			printf("%x | ", node_get_value(temp));
			temp = node_get_next(temp);
		}
	}
	printf("\n");
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 stack.c node.c -o stacktest
// run with: ./stacktest [<num>]...

/*int main(int argc, const char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./stacktest [<num>]...\n");
		return 1;
	}

	stack_t* pila =	stack_init();

	int val;
	for (int i = 1; i < argc; ++i) {
		val = atoi(argv[i]);
		stack_push(pila, val);
		// printf("Stack top is: %d\n", stack_get_top(pila));
		stack_print(pila);
	}

	// for (int i = 1; i < argc; ++i) {
	// 	printf("Popping: %d\n", stack_pop(pila));
	// }


	stack_destroy(pila);

	return 0;
}*/
