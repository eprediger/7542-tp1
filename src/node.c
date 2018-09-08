#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void node_init(node_t* self, int value) {
	self->_value = value;
	self->_next = NULL;
}

void node_destroy(node_t* self) { }

int node_get_value(node_t* self) {
	return self->_value;
}

node_t* node_get_next(node_t* self) {
	return self->_next;
}

void node_set_next(node_t* self, node_t* next_node) {
	self->_next = next_node;
}
