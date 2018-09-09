#include "vars.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void vars_init(var_array_t* self, const size_t dim) {
	self->_size = dim;
	self->_vars = malloc(dim * sizeof(*self->_vars));
	memset(self->_vars, 0, dim * sizeof(*self->_vars));
}

void vars_destroy(var_array_t* self) {
	free(self->_vars);
}

int* vars_get_array(var_array_t* self) {
	return self->_vars;
}

size_t vars_get_array_size(var_array_t* self) {
	return self->_size;
}

int vars_get_variable_by_index(var_array_t* self, size_t index) {
	return self->_vars[index];
}

void vars_set_variable_by_index(var_array_t* self, size_t index, int value) {
	self->_vars[index] = value;
}
