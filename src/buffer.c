#include "buffer.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <arpa/inet.h>

#define BUF_SIZE 100

#define IAND	0x7E
#define IOR		0x80
#define IXOR	0x82
#define INEG	0x74

#define IADD	0x60
#define ISUB	0x64
#define IMUL	0x68
#define IDIV	0x6C
#define IREM	0x70

#define DUP		0x59
#define BIPUSH	0x10

#define ISTORE	0x36
#define ILOAD	0x15

void buffer_init(buffer_t* self) {
	self->_max_size = BUF_SIZE;
	self->_data = malloc(sizeof(*self->_data) * BUF_SIZE);
	self->_numbers = malloc(sizeof(*self->_numbers) * BUF_SIZE);

	buffer_reset(self);
}

void buffer_destroy(buffer_t* self) {
	free(self->_data);
	free(self->_numbers);
}

void buffer_reset(buffer_t* self) {
	self->_current_size = 0;
	memset(self->_data, 0, sizeof(*self->_data) * BUF_SIZE);
	memset(self->_numbers, 0, sizeof(*self->_numbers) * BUF_SIZE);
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

static bool is_instruction(unsigned char dato) {
	return ((dato == IAND) || \
			(dato == IOR)  || \
			(dato == IXOR) || \
			(dato == INEG) || \
			(dato == IADD) || \
			(dato == ISUB) || \
			(dato == IMUL) || \
			(dato == IDIV) || \
			(dato == IREM) || \
			(dato == DUP)  || \
			(dato == BIPUSH) || \
			(dato == ISTORE) || \
			(dato == ILOAD));
}

void buffer_transform_data(buffer_t* self, size_t elem) {
	for (int i = 0; i < elem; i++) {
		if (is_instruction(self->_data[i])) {
			self->_numbers[i] = (unsigned char) self->_data[i];
		} else {
			self->_numbers[i] = (char) self->_data[i];
		}
	}
	self->_current_size = elem;	
}

int* buffer_get_transformed_data(buffer_t* self) {
	return self->_numbers;
}

void buffer_htonl(int* data, int data_size) {
	for (int i = 0; i < data_size; ++i) {
		data[i] = htonl(data[i]);
	}
}

void buffer_ntohl(int* data, int data_size) {
	for (int i = 0; i < data_size; ++i) {
		data[i] = ntohl(data[i]);
	}
}
