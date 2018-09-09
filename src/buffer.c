#include "buffer.h"

#include <string.h>
#include <stdio.h>

#define BUF_SIZE 100
#define BASE 16
#define MOVE 1

void buffer_init(buffer_t* self) {
	self->_max_size = BUF_SIZE;
	self->_data = malloc(sizeof(*self->_data) * BUF_SIZE);
	self->_numbers = malloc(sizeof(*self->_numbers) * BUF_SIZE);

	buffer_reset(self);
	/*self->_current_size = 0;
	memset(self->_data, 0, sizeof(*self->_data) * BUF_SIZE);
	memset(self->_numbers, 0, sizeof(*self->_numbers) * BUF_SIZE);*/
}

void buffer_destroy(buffer_t* self) {
	free(self->_data);
	free(self->_numbers);
}

void buffer_reset(buffer_t* self) {
	self->_current_size = 0;
	memset(self->_data, 0, sizeof(*self->_data) * self->_max_size);
	memset(self->_numbers, 0, sizeof(*self->_numbers) * self->_max_size);
}

size_t buffer_get_size(buffer_t* self) {
	return self->_current_size;
}

size_t buffer_get_max_size(buffer_t* self) {
	return self->_max_size;
}

void buffer_set_data(buffer_t* self, const unsigned char* ptr, size_t size) {
	memcpy(self->_data, ptr, size);
}

void buffer_transform_data(buffer_t* self, size_t elem) {
	char* str;
	str = malloc(sizeof(*str));
	for (int i = 0; i < elem; i++) {
		self->_numbers[i] = (int) self->_data[i];
	}
	self->_current_size = elem;	
	free(str);
}

int* buffer_get_transformed_data(buffer_t* self) {
	return self->_numbers;
}
