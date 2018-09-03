#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "socket.h"
#include "parser.h"
#include "vars.h"

typedef struct {
	socket_t* client_socket;
	parser_t* parser;
	var_array_t* variables;
} client_t;

// PRE:  
// POST: 
client_t* client_init();

// PRE:  
// POST: 
void client_destroy(client_t* self);

// PRE:  
// POST: 
void client_connect(client_t* self);

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
