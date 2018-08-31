#include "parser.h"

#include <stdlib.h>

#define COUNT 1

parser_t* parser_init(const char* filepath) {
	parser_t* self = malloc(sizeof(parser_t));
	self->bytecode = malloc(sizeof(*self->bytecode) * COUNT);
	
	if (filepath == NULL) {
		self->file = stdin;
	} else {
		self->file = fopen(filepath, "rb");
	}

	return self;
}

void parser_destroy(parser_t* self) {
	fclose(self->file);
	free(line);
	free(self);
}

size_t parser_read_element(parser_t* self) {
	// size_t elements = 
	return fread((int*)self->bytecode, sizeof(*self->bytecode), COUNT, self);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 parser.c vmachine.c vars.c stack.c node.c -o parsertest

// run with: ./parsertest <num-vars> <filename>

int main(int argc, const char *argv[]) {
	parser_t* parser;

	switch (argc) {
		case 2:
			parser = parser_init(NULL);
			break;

		case 3:
			parser = parser_init(argv[2]);
			break;

		default:
			printf("Usage: ./parsertest <num-vars> [<filename>]\n");
			return 1;
	}

	size_t read_element = 

	do {
		parser_read(parser);

	} while

	parser_destroy(parser);

	return 0;
}
