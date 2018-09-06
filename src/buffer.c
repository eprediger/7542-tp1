#include "buffer.h"

#include <string.h>
#include <stdio.h>

#define BASE 16

void buffer_init(buffer_t* self, unsigned int size) {
	self->_max_size = size;
	self->_current_size = 0;
	self->_data = malloc(sizeof(*self->_data) * size);
	self->_numbers = malloc(sizeof(*self->_numbers) * size);

	memset(self->_data, 0, sizeof(*self->_data) * size);
	memset(self->_numbers, 0, sizeof(*self->_numbers) * size);
}

void buffer_destroy(buffer_t* self) {
	free(self->_data);
	free(self->_numbers);
}

char* buffer_get_data(buffer_t* self) {
	return self->_data;
}

void buffer_reset_buffer(buffer_t* self) {
	self->_current_size = 0;
	memset(self->_data, 0, sizeof(*self->_data) * self->_max_size);
	memset(self->_numbers, 0, sizeof(*self->_numbers) * self->_max_size);
}

void buffer_transform_data(buffer_t* self, size_t elem) {
	char str[2];
	// printf("Elementos leidos: %lu\n", elem);
	for (int i = 0; i < elem; ++i) {
		sprintf(&str[0], "%2x", self->_data[i]);
		printf("str: %s | ", str);
		self->_numbers[i] = (int) strtol(&str[0], NULL, BASE);
		printf("num: %x\n", self->_numbers[i]);
	}
	self->_current_size = elem;
}