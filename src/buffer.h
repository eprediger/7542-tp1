#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdlib.h>	// size_t

typedef struct buffer {
	size_t _max_size;	// privado
	size_t _current_size;	// privado
	unsigned char* _data;	// privado
	int* _numbers;	// privado
} buffer_t;

// PRE:  -
// POST: Crea un doble buffer de datos el cual permite
// almacenar tanto caracteres y numeros con signo
void buffer_init(buffer_t* self);

// PRE:  buffer creado mediante buffer_init
// POST: libera los recursos asociados a la instancia self
void buffer_destroy(buffer_t* self);

// PRE:  buffer creado mediante buffer_init
// POST: se eliminan todos los datos contenidos
// en el buffer tanto caracteres como numericos
void buffer_reset(buffer_t* self);

// PRE:  buffer creado mediante buffer_init
// POST: devuelve la cantidad de datos
// válidos alojados en el buffer
size_t buffer_get_size(buffer_t* self);

// PRE:  buffer creado mediante buffer_init
// POST: devuelve la capacidad máxima del buffer
size_t buffer_get_max_size(buffer_t* self);

// PRE:  buffer creado mediante buffer_init
// POST: el buffer contiene los "size" caracteres
// pasados por el parametro ptr
void buffer_set_data(buffer_t* self, const unsigned char* ptr, size_t size);

// PRE:  buffer con datos previamente con buffer_set_data
// POST: transforma los datos alojados en data en formato entero
void buffer_transform_data(buffer_t* self, size_t elem);

// PRE:  los datos del buffer fueron previamente
// transformados con buffer_transform_data
// POST: devuelve los datos en formato entero
int* buffer_get_transformed_data(buffer_t* self);

#endif
