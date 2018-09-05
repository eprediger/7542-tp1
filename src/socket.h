#ifndef __SOCKET_H__
#define __SOCKET_H__

typedef struct {
	struct addrinfo* _address;	// privado
	int _socket;	// privado
} socket_t;

socket_t* socket_init(const char *node, const char* service, int flags);

void socket_destroy(socket_t* self);

void socket_bind(socket_t* self);

void socket_listen(socket_t* self, int max_request);

void socket_accept(socket_t* self, socket_t* client_socket);

void socket_connect(socket_t* self);

void socket_send(socket_t* self, const char* buf, const int size);

void socket_receive(socket_t* self, char* buf, int size);

void socket_close_write_channel(socket_t* self);

void socket_close_connection(socket_t* self);

#endif
