#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdlib.h>

typedef struct socket {
	struct addrinfo* _address;	// privado
	int _socket;	// privado
} socket_t;

void socket_init(socket_t* self, const char *node, const char* serv, int flags);

void socket_destroy(socket_t* self);

void socket_bind(socket_t* self);

void socket_listen(socket_t* self, int max_request);

void socket_accept(socket_t* self, socket_t* client_socket);

void socket_connect(socket_t* self);

int socket_send(socket_t* self, const int* buf, const size_t size);

int socket_receive(socket_t* self, int* buf, size_t size);

void socket_close_write_channel(socket_t* self);

void socket_close_connection(socket_t* self);

#endif
