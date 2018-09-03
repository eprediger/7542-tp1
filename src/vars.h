#ifndef __VARS_H__
#define __VARS_H__

typedef struct var_array {
	int* vars;
	unsigned int size;
} var_array_t;

// Devuelve una instancia de var_array_t
// de tamanio dim
// PRE:  -
// POST: var_array_t apunta a un sector 
// válido de memoria.
var_array_t* vars_init(const unsigned int dim);

// Libera recursos asociados a self
// PRE:  self iniciado mediante vars_init
// POST: self no apunta a un sector válido
void vars_destroy(var_array_t* self);

// 
// PRE:  
// POST: 
unsigned int vars_get_array_size(var_array_t* self);

// Retorna valor en posicion indicada
// PRE:  self iniciado mediante vars_init
//       0 < index < dim array
// POST: no se modifica el vector
int vars_get_variable_by_index(var_array_t* self, int index);

// Modifica el valor del indice indicado en el array
// PRE:  self iniciado mediante vars_init
//       index < dim array
// POST: array en indice index toma valor value
void vars_set_variable_by_index(var_array_t* self, int index, int value);

// Imprime por salida estandar el contenido del
// array en notación hexadecimal de 8 dígitos
// PRE:  self iniciado mediante vars_init
// POST: -
// void vars_print_vars_with_format(var_array_t* self);

#endif
