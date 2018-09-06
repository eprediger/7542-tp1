#include "parser.h"

#include <stdlib.h>	// exit, EXIT_SUCCESS, EXIT_FAILURE, size_t
#include <string.h>	// strerror
#include <errno.h>	// errno

#define BUF_SIZE 100

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
	buffer_init(&(self->_buffer), BUF_SIZE);
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
	// size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
	char* ptr = buffer_get_data(&(self->_buffer));
	size_t size = sizeof(*ptr);
	size_t count = BUF_SIZE;
	FILE* stream = self->_file;
	size_t read_elem = fread(ptr, size, count, stream);

	if (self->_file == stdin) {
		read_elem--;
	}
	buffer_transform_data(&(self->_buffer), read_elem);
}
