#include "socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define _POSIX_C_SOURCE 200112L

socket_t* socket_create() {
	socket_t* self = malloc(sizeof(socket_t));
	self->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (self->socket == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
	}

	return self;
}

socket_t* socket_init(const struct addrinfo* address) {
	socket_t* self = malloc(sizeof(socket_t));
	self->address = address;

	int domain = address->ai_family;
	int type = address->ai_socktype;
	int protocol = address->ai_protocol;
	self->socket = socket(domain, type, protocol);
	if (self->socket == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return 1;
	}

	return self;
}

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

void socket_send(socket_t* self, char* buf, int size) {
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
