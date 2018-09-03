#include "client.h"

#include "socket.h"
#include "parser.h"
#include "vars.h"

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define MESSAGE_SIZE 4

//	"Variables dump\n"
#define VAR_DUMP_MSG_SIZE 15
//	"00000000\n"
#define VAR_PRINT_SIZE 9

client_t* client_init(const char* file, const int size) {
	client_t* self = malloc(sizeof(client_t));
	//self->client_socket = socket_init();
	self->parser = parser_init(file);
	self->num_variables = size;
	return self;
}

void client_destroy(client_t* self) {
	parser_destroy(self->parser);
	socket_destroy(self->client_socket);
	free(self);
}

void client_connect(client_t* self, const char* host, const char* service) {
	self->client_socket = socket_init(host, service, 0);

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
	int len_message = VAR_DUMP_MSG_SIZE + (VAR_PRINT_SIZE * self->num_variables);
	char message[len_message];
	memset(message, 0, len_message);	
	socket_receive(self->client_socket, message, len_message - 1);

	fprintf(stdout, "%s\n", message);
}

void client_disconnect(client_t* self) {
	socket_close_connection(self->client_socket);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 client.c parser.c vmachine.c vars.c stack.c node.c -o testclient
// run with: ./testclient <host> <port>
