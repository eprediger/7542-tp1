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
void parser_read();

#endif
