#ifndef __PARSER_H__
#define __PARSER_H__

#include "buffer.h"

#include <stdio.h>	// FILE*, stdin, fopen(), fprintf, feof

typedef struct parser {
	FILE* _file;	// privado
	buffer_t _buffer;	// privado
} parser_t;

void parser_init(parser_t* self, const char* filepath);
void parser_destroy(parser_t* self);
int parser_feof(parser_t* self);
void parser_read(parser_t* self);

#endif
