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
// void stack_print(stack_t* self) {
// 	printf("%s", "Stack: ");
// 	node_t* temp = self->_top;
// 	while (temp != NULL) {
// 		printf("%x | ", node_get_value(temp));
// 		temp = node_get_next(temp);
// 	}
// 	printf("\n");
// }
