#ifndef __SERVER_H__
#define __SERVER_H__ 

#include "vmachine.h"
#include "socket.h"
#include "buffer.h"

typedef struct {
	socket_t _local_socket;
	socket_t _remote_socket;
	vmachine_t _virtual_machine;
	buffer_t _buffer;
} server_t;

// PRE:  
// POST: 
void server_init(server_t* self, const char* service);

// PRE:  
// POST: 
void server_destroy(server_t* self);

// PRE:  
// POST: 
int server_start(server_t* self);

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
