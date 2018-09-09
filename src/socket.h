#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdlib.h>

typedef struct socket {
	struct addrinfo* _address;	// privado
	int _socket;	// privado
} socket_t;

// PRE:  node corresponde a un host, ip o url
//		 servicio puede invocarse por nombre o numero de puerto
//		 flags debe ser AI_PASSIVE para un socket servidor, 0 para un cliente
// POST: inicializa el socket, en caso de error retorna -1
int socket_init(socket_t* self, const char *node, const char* serv, int flags);

// PRE:  socket inicializado mediante socket_init
// POST: libera recursos asociados a la instancia self, cerrando el socket
void socket_destroy(socket_t* self);

// PRE:  socket inicializado mediante socket_init
// POST: socket asociado al puerto "service" de socket_init
void socket_bind(socket_t* self);

// PRE:  socket bindeado a un puerto mediante socket_bind
// POST: socket escuchando conexiones entrantes en el puerto "service"
void socket_listen(socket_t* self, int max_request);

// PRE:  socket escuchando un puerto mediante socket_listen
// POST: socket acepta una conexión entrante, luego se cierra
void socket_accept(socket_t* self, socket_t* client_socket);

// PRE:  socket inicializado mediante socket_init
// POST: intenta conexión al host y puerto contenido 
// en _address, retornando 0. En caso de error retorna -1
int socket_connect(socket_t* self);

// PRE:  socket_connect (cliente) o socket_accept (servidor)
// POST: envia a través de self size bytes el contenido de buf
int socket_send(socket_t* self, const int* buf, const size_t size);

// PRE:  socket_connect (cliente) o socket_accept (servidor)
// POST: recibe a través de self size bytes que alojaran en buf
int socket_receive(socket_t* self, int* buf, size_t size);

// PRE:  socket inicializado mediante socket_init
// POST: cierra el canal de escritura de self
void socket_close_write_channel(socket_t* self);

// PRE:  socket inicializado mediante socket_init
// POST: cierra canal de lectura y escritura de self
void socket_close_connection(socket_t* self);

#endif
