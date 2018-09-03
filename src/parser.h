#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>

typedef struct {
	FILE* file;
	char* bytecode;
} parser_t;

// 
// PRE:  
// POST: 
parser_t* parser_init(const char* filepath);

// 
// PRE:  
// POST: 
void parser_destroy(parser_t* self);

// 
// PRE:  
// POST: 
void parser_read(parser_t* self);

// 
// PRE:  
// POST: 
char* parser_get_bytecode(parser_t* self);

// 
// PRE:  
// POST: 
size_t parser_length(parser_t* self);

// 
// PRE:  
// POST: 
int parser_eof(parser_t* self);

#endif
