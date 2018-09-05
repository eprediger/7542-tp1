#ifndef __SERVER_H__
#define __SERVER_H__ 

#include "vmachine.h"
#include "socket.h"

typedef struct {
	socket_t* local_socket;
	socket_t* remote_socket;
	vmachine_t* virtual_machine;
	buffer_t buffer;
} server_t;

// PRE:  
// POST: 
server_t* server_init(const char* service);

// PRE:  
// POST: 
void server_destroy(server_t* self);

// PRE:  
// POST: 
void server_start(server_t* self);

// PRE:  
// POST: 
void server_print_variables_dump(server_t* self);

// PRE:  
// POST: 
void server_send_variables_dump(server_t* self);

// PRE:  
// POST: 
void server_stop(server_t* self);

#endif
