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

var_array_t* vars_init(const int dim) {
	var_array_t* self = malloc(sizeof(var_array_t));
	self->size = dim;
	self->vars = malloc(dim * sizeof(*self->vars));
	memset(self->vars, 0, dim * sizeof(*self->vars));

	return self;
}

void vars_destroy(var_array_t* self) {
	if (self != NULL) {
		free(self->vars);
		free(self);
	}
}

int vars_get_variable_by_index(var_array_t* self, int index) {
	return self->vars[index];
}

void vars_set_variable_by_index(var_array_t* self, int index, int value) {
	self->vars[index] = value;
}

void vars_print_vars_with_format(var_array_t* self) {
	for (int i = 0; i < self->size; ++i) {
		// printf("variables[%d] = %08x | ", i, vars_get_variable_by_index(self, i)); FOR TESTING
		printf("%08x\n", vars_get_variable_by_index(self, i));
	}
	printf("\n");
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 vars.c -o varstest
// run with: ./varstest <size>

/*int main(int argc,  const char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./varstest <size>\n");
		return 1;
	}

	int dim = atoi(argv[1]);

	var_array_t* variables = vars_init(dim);

	int temp;
	for (int i = 0; i < dim; ++i) {
		printf("Dame un numero: ");
		scanf("%d", &temp);
		vars_set_variable_by_index(variables, i, temp);
	}
	
	vars_print_vars_with_format(variables);	

	vars_destroy(variables);

	return 0;
}*/
