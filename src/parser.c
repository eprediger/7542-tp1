#include "parser.h"

#include <stdlib.h>	// exit, EXIT_SUCCESS, EXIT_FAILURE, size_t
#include <string.h>	// strerror
#include <errno.h>	// errno


void parser_init(parser_t* self, const char* filepath) {
	if (filepath == NULL) {
		self->_file = stdin;
	} else {
		self->_file = fopen(filepath, "r");
		if (self->_file == NULL) {
			fprintf(stderr, "Error opening file %s: %s\n", filepath, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	buffer_init(&(self->_buffer));
}

void parser_destroy(parser_t* self) {
	buffer_destroy(&(self->_buffer));
	if (self->_file != stdin) {
		fclose(self->_file);
	}
}

int parser_feof(parser_t* self) {
	return feof(self->_file);
}

void parser_read(parser_t* self) {
	buffer_reset_buffer(&(self->_buffer));

	char* temp = malloc(sizeof(char) * buffer_get_max_size(&self->_buffer));
	size_t size = sizeof(*temp);
	size_t count = buffer_get_max_size(&self->_buffer);
	FILE* stream = self->_file;
	size_t read_elem = fread(temp, size, count, stream);

	if (self->_file == stdin) {
		read_elem--;
	}
	buffer_set_data(&(self->_buffer), temp, read_elem);
	buffer_transform_data(&(self->_buffer), read_elem);
	free(temp);
}

buffer_t parser_get_buffer(parser_t* self) {
	return self->_buffer;
}
