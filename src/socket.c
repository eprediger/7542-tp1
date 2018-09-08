#define _POSIX_C_SOURCE 200112L

#include "socket.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void socket_init(socket_t* self, const char *node,\
				 const char* serv, int flags) {
	int s = 0;
	struct addrinfo hints;
	struct addrinfo* result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;			// IPv4
	hints.ai_socktype = SOCK_STREAM;	// TCP
	hints.ai_flags = flags;				// Server: AI_PASSIVE | Client: 0

	s = getaddrinfo(node, serv, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(s));
		// socket_destroy(self);
		exit(EXIT_FAILURE);
	}

	self->_address = result;

	int domain = result->ai_family;
	int type = result->ai_socktype;
	int protocol = result->ai_protocol;

	self->_socket = socket(domain, type, protocol);
}

void socket_destroy(socket_t* self) {
	freeaddrinfo(self->_address);
	close(self->_socket);
}

void socket_bind(socket_t* self) {
	struct sockaddr* address = self->_address->ai_addr;
	socklen_t address_len = self->_address->ai_addrlen;

	int s = bind(self->_socket, address, address_len);
	if (s == -1) {
		fprintf(stderr, "binding error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

void socket_listen(socket_t* self, int max_request) {
	int error = 0;
	error = listen(self->_socket, max_request);

	if (error == -1) {
		fprintf(stderr, "listening error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

void socket_accept(socket_t* self, socket_t* client_socket) {
	client_socket->_socket = accept(self->_socket, NULL, NULL);
}

void socket_connect(socket_t* self) {
	struct sockaddr* address = self->_address->ai_addr;
	socklen_t address_len = self->_address->ai_addrlen;
	
	int s = connect(self->_socket, address, address_len);
	if (s == -1) {
		fprintf(stderr, "connection error: %s\n", strerror(errno));
		socket_destroy(self);
		exit(EXIT_FAILURE);
	}
}

int socket_send(socket_t* self, const int* buf, const size_t size) {
	int sent = 0;
	int length_sent = 0;
	bool open_socket = true;
	bool valid_socket = true;

	while ((sent < size) && (valid_socket) && (open_socket)) {
		int remaining = size - sent;
		length_sent = send(self->_socket, &buf[sent], remaining, MSG_NOSIGNAL);

		if (length_sent < 0) {	// Error al enviar
			fprintf(stderr, "sending error: %s\n", strerror(errno));
			valid_socket = false;
		} else if (length_sent == 0) {	// Socket cerrado
			open_socket = false;
		} else {
			sent += length_sent;
		}
	}

	return sent;
}

int socket_receive(socket_t* self, int* buf, size_t size) {
	int received = 0;
	int len_recv = 0;
	bool open_socket = true;
	bool valid_socket = true;

	while ((received < size) && (valid_socket) && (open_socket)) {
		int remaining = size - received;
		len_recv = recv(self->_socket, &buf[received], remaining, MSG_NOSIGNAL);
		
		if (len_recv < 0) {
			fprintf(stderr, "receiving error: %s\n", strerror(errno));
			valid_socket = false;
		} else if (len_recv == 0) {
			open_socket = false;
		} else {
			received += len_recv;
		}
	}
	return received;
}

void socket_close_write_channel(socket_t* self) {
	shutdown(self->_socket, SHUT_WR);
}

void socket_close_connection(socket_t* self) {
	shutdown(self->_socket, SHUT_RDWR);	
}
