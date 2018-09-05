#include "stack.h"

#include <stdio.h>

void stack_init(stack_t* self) {
	self->_top = NULL;
}

void stack_destroy(stack_t* self) {
	while (self->_top != NULL) {
		stack_pop(self);
	}
}

void stack_push(stack_t* self, int val) {
	node_t* nodo = malloc(sizeof(node_t));
	node_init(nodo, val);
	node_set_next(nodo, self->_top);
	self->_top = nodo;
}

int stack_pop(stack_t* self) {
	int popped_value = node_get_value(self->_top);
	
	node_t* old_top = self->_top;
	self->_top = node_get_next(self->_top);

	free(old_top);

	return popped_value;
}

int stack_get_top(stack_t* self) {
	return node_get_value(self->_top);
}

/* FOR TESTING ONLY */
void stack_print(stack_t* self) {
	printf("%s", "Stack: ");
	node_t* temp = self->_top;
	while (temp != NULL) {
		printf("%x | ", node_get_value(temp));
		temp = node_get_next(temp);
	}
	printf("\n");
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 stack.c node.c -o ../test/teststack
// run with: ../test/teststack <num>...

/*int main(int argc, const char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./stacktest <num>...\n");
		return 1;
	}

	stack_t pila;
	stack_init(&pila);

	int val;
	for (int i = 1; i < argc; ++i) {
		val = atoi(argv[i]);
		stack_push(&pila, val);
		printf("Stack top is: %d\n", stack_get_top(&pila));
		stack_print(&pila);
	}

	// for (int i = 1; i < argc; ++i) {
	// 	printf("Popping: %d\n", stack_pop(&pila));
	// }


	stack_destroy(&pila);

	return 0;
}*/
