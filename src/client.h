#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "socket.h"
#include "parser.h"
#include "vars.h"

typedef struct {
	socket_t _client_socket;
	parser_t _parser;
	int _num_variables;
} client_t;

// PRE:  
// POST: 
void client_init(client_t* self, const char* file, const int variables);

// PRE:  
// POST: 
void client_destroy(client_t* self);

// PRE:  
// POST: 
void client_connect(client_t* self, const char* host, const char* service);

// PRE:  
// POST: 
void client_send_vars_size(client_t* self, const char* num_variables);

// PRE:  
// POST: 
void client_send_bytecodes(client_t* self);

// PRE:  
// POST: 
void client_receive_variable_dump(client_t* self);

// PRE:  
// POST: 
void client_disconnect(client_t* self);

#endif
