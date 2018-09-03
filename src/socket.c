#define _POSIX_C_SOURCE 200112L

#include "socket.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

/*socket_t* socket_create() {
	socket_t* self = malloc(sizeof(socket_t));
	
	self->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (self->socket == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
	}

	return self;
}*/

socket_t* socket_init(const char *node, const char* service, int flags) {
	socket_t* self = malloc(sizeof(socket_t));
	
	int s = 0;
	struct addrinfo hints;
	struct addrinfo* result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = flags;     // Server

	s = getaddrinfo(node, service, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(s));
		free(self);
		exit(EXIT_FAILURE);
	}

	self->address = result;

	int dominio = result->ai_family;
	int tipo = result->ai_socktype;
	int protocolo = result->ai_protocol;
	self->socket = socket(dominio, tipo, protocolo);


	freeaddrinfo(result);

	return self;
}

// int socket(int domain, int type, int protocol);
// socket_t* socket_init(struct addrinfo* address) {

// socket_t* socket_init(int domain, int type, int protocol) {
// 	socket_t* self = malloc(sizeof(socket_t));
// 	// self->address = address;

// 	// int domain = address->ai_family;
// 	// int type = address->ai_socktype;
// 	// int protocol = address->ai_protocol;
// 	self->socket = socket(domain, type, protocol);
// 	if (self->socket == -1) {
// 		fprintf(stderr, "Error: %s\n", strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}

// 	return self;
// }

void socket_destroy(socket_t* self) {
	close(self->socket);
	free(self);
}

void socket_bind(socket_t* self) {
	struct sockaddr* address = self->address->ai_addr;
	socklen_t address_len = self->address->ai_addrlen;

	int s = bind(self->socket, address, address_len);
	if (s == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

void socket_listen(socket_t* self, int max_request) {
	int error = 0;
	error = listen(self->socket, max_request);

	if (error == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

void socket_accept(socket_t* self, socket_t* client_socket) {
	client_socket->socket = accept(self->socket, NULL, NULL);
}

// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void socket_connect(socket_t* self) {
	struct sockaddr* address = self->address->ai_addr;
	socklen_t address_len = self->address->ai_addrlen;
	
	int s = connect(self->socket, address, address_len);
	if (s == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

void socket_send(socket_t* self, const char* buf, const int size) {
	int sent = 0;
	int length_sent = 0;
	bool valid_socket = true;

	while ((sent < size) && valid_socket) {
		int remaining = size - sent;
		length_sent = send(self->socket, &buf[sent], remaining, MSG_NOSIGNAL);

		if (length_sent < 0) {	// Error al enviar
			fprintf(stderr, "Error: %s\n", strerror(errno));
			valid_socket = false;
		} else if (length_sent == 0) {	// Socket cerrado
			valid_socket = false;
		} else {
			sent += length_sent;
		}
	}
}

void socket_receive(socket_t* self, char* buf, int size) {
	int received = 0;
	int length_received = 0;
	bool valid_socket = true;

	while ((received < size) && valid_socket) {
		int remaining = size - received;
		length_received = recv(self->socket, &buf[received], remaining, MSG_NOSIGNAL);
		
		if (length_received == 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			valid_socket = false;
		} else if (length_received < 0) {
			valid_socket = false;
		} else {
			received += length_received;
		}
	}
}

void socket_close_write_channel(socket_t* self) {
	shutdown(self->socket, SHUT_WR);
}

void socket_close_connection(socket_t* self) {
	shutdown(self->socket, SHUT_RDWR);	
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 socket.c parser.c vmachine.c vars.c stack.c node.c -o testsocket
// run with: ./testsocket <host> <port>
