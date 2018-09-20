#ifndef __PARSER_H__
#define __PARSER_H__

#include "buffer.h"

#include <stdio.h>	// FILE*, stdin, fopen(), fprintf, feof

typedef struct parser {
	FILE* _file;	// privado
	buffer_t _buffer;	// privado
} parser_t;

// PRE:  filepath debe ser una ruta a un archivo válida o NULL
// POST: inicializa el parser con el filepath indicado, 
// si se pasa NULL se asociara la instancia a standard input
void parser_init(parser_t* self, const char* filepath);

// PRE:  parser inicializado mediante parser_init
// POST: libera los recursos asociados a la instancia
void parser_destroy(parser_t* self);

// PRE:  parser inicializado mediante parser_init
// POST: indica si se ha alcanzado o no el final del archivo
int parser_feof(parser_t* self);

// PRE:  parser inicializado mediante parser_init
// POST: lee del archivo tantos caracteres del archivo
// como la capacidad del buffer y los guarda en el buffer
void parser_read(parser_t* self);

// PRE:  parser inicializado mediante parser_init
// POST: retorna el buffer de la instancia self
buffer_t parser_get_buffer(parser_t* self);

#endif
