#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdlib.h>	// size_t

typedef struct buffer {
	unsigned int _max_size;	// privado
	unsigned int _current_size;	// privado
	char* _data;	// privado
	int* _numbers;	// privado
} buffer_t;

void buffer_init(buffer_t* self);

void buffer_destroy(buffer_t* self);

void buffer_reset_buffer(buffer_t* self);

unsigned int buffer_get_size(buffer_t* self);

unsigned int buffer_get_max_size(buffer_t* self);

void buffer_set_data(buffer_t* self, const char* ptr, size_t size);

void buffer_transform_data(buffer_t* self, size_t elem);

int* buffer_get_transformed_data(buffer_t* self);

int buffer_get_transformed_data_by_index(buffer_t* self, int index);

#endif
