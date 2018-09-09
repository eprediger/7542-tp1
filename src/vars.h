#ifndef __VARS_H__
#define __VARS_H__

#include <stdlib.h>

typedef struct var_array {
	int* _vars;	// privado
	size_t _size;	// privado
} var_array_t;

// PRE:  -
// POST: crea un arreglo de variables de dimension dim
void vars_init(var_array_t* self, const size_t dim);

// PRE:  self iniciado mediante vars_init
// POST: libera recursos asociados a self
void vars_destroy(var_array_t* self);

// PRE:  self iniciado mediante vars_init
// POST: devuelve el arreglo de variables
int* vars_get_array(var_array_t* self);

// PRE:  self iniciado mediante vars_init
// POST: retorna la dimension del arreglo
size_t vars_get_array_size(var_array_t* self);

// PRE:  self iniciado mediante vars_init
//       0 <= index < dim array-1
// POST: retorna valor en posicion indicada
int vars_get_variable_by_index(var_array_t* self, size_t index);

// PRE:  self iniciado mediante vars_init
//       0 <= index < dim array-1
// POST: el array en indice index toma valor value
void vars_set_variable_by_index(var_array_t* self, size_t index, int value);

#endif
