#include "client.h"

#include "socket.h"
#include "parser.h"
#include "vars.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 4

client_t* client_init(const char* file, const int size) {
	client_t* self = malloc(sizeof(client_t));
	//self->client_socket = socket_init();
	self->parser = parser_init(file);
	self->variables = vars_init(size);

	return self;
}

void client_destroy(client_t* self) {
	vars_destroy(self->variables);
	parser_destroy(self->parser);
	socket_destroy(self->client_socket);
	free(self);
}

void client_connect(client_t* self, const char* host, const char* service) {
	int s = 0;
	struct addrinfo hints;
	struct addrinfo* result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = 0;              // None (client)

	s = getaddrinfo(host, service, &hints, &result);
	if (s != 0) { 
		fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	self->client_socket = socket_init(result);

	freeaddrinfo(result);

	socket_connect(self->client_socket);
}

void client_send_vars_size(client_t* self, const char* num_variables) {
	int len_message = strlen(num_variables);
	socket_send(self->client_socket, num_variables, len_message);
}

void client_send_bytecodes(client_t* self) {
	while (!parser_eof(self->parser)) {
		parser_read(self->parser);
		char* instruction = parser_get_bytecode(self->parser);
		size_t length_instruction = parser_length(self->parser);
		socket_send(self->client_socket, instruction, length_instruction);
	}
	socket_close_write_channel(self->client_socket);
}

void client_receive_variable_dump(client_t* self) {
	
}

void client_disconnect(client_t* self) {
	socket_close_connection(self->client_socket);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 client.c parser.c vmachine.c vars.c stack.c node.c -o testclient
// run with: ./testclient <host> <port>
