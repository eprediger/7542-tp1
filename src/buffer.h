#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdlib.h>	// size_t

typedef struct buffer {
	unsigned int _max_size;	// privado
	int _current_size;	// privado
	char* _data;	// privado
	int* _numbers;	// privado
} buffer_t;

void buffer_init(buffer_t* self, unsigned int size);
void buffer_destroy(buffer_t* self);
char* buffer_get_data(buffer_t* self);
void buffer_reset_buffer(buffer_t* self);
void buffer_transform_data(buffer_t* self, size_t elem);

#endif
