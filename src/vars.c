/* 
 * El array de variables tiene una dimensión fija de N números enteros int
 * inicializados a 0, donde N es un parámetro del programa cliente y es
 * recibido por socket por el servidor.
 *
 * imprimir por salida estándar el contenido del array de variables imprimiendo
 * cada número en su propia línea en notación hexadecimal de 8 dígitos.
 */

#include "vars.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void vars_init(var_array_t* self, const unsigned int dim) {
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

unsigned int vars_get_array_size(var_array_t* self) {
	return self->_size;
}

int vars_get_variable_by_index(var_array_t* self, int index) {
	return self->_vars[index];
}

void vars_set_variable_by_index(var_array_t* self, int index, int value) {
	self->_vars[index] = value;
}

/* FOR TESTING ONLY */
void vars_print_vars_with_format(var_array_t* self) {
	printf("%s\n", "\nVariables dump");
	
	for (int i = 0; i < self->_size; ++i) {
		fprintf(stdout, "%08x\n", vars_get_variable_by_index(self, i));
	}
}
