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

//	"Variables dump\n"
#define VAR_DUMP_MSG_SIZE 15
//	"00000000\n"
#define VAR_PRINT_SIZE 9

#define BASE 10

void client_init(client_t* self, const char* file, const int variables) {
	//self->_client_socket = socket_init();
	parser_init(&(self->_parser), file);
	// buffer_init(&self->_buffer);
	self->_num_variables = variables;
}

void client_destroy(client_t* self) {
	// buffer_destroy(&self->_buffer);
	parser_destroy(&self->_parser);
	socket_destroy(&self->_client_socket);
}

void client_connect(client_t* self, const char* host, const char* service) {
	socket_init(&self->_client_socket, host, service, 0);

	socket_connect(&self->_client_socket);
}

void client_send_vars_size(client_t* self, const char* num_variables) {
	int vars = (int) strtol(num_variables, NULL, BASE);
	vars = htonl(vars);
	socket_send(&self->_client_socket, &vars, sizeof(vars));
}

static void client_buf_tonl(int* data, int data_size) {
	for (int i = 0; i < data_size; ++i) {
		data[i] = htonl(data[i]);
	}
}

void client_send_bytecodes(client_t* self) {
	while(!parser_feof(&self->_parser)) {
		parser_read(&self->_parser);

		buffer_t temp_buffer = parser_get_buffer(&self->_parser);
		int* bytecodes = buffer_get_transformed_data(&temp_buffer);
		int send_size = buffer_get_size(&temp_buffer);
		client_buf_tonl(bytecodes, send_size);
		size_t send_size_b = send_size * sizeof(*bytecodes);
		socket_send(&self->_client_socket, bytecodes, send_size_b);
	}

	socket_close_write_channel(&self->_client_socket);
}

void client_receive_variable_dump(client_t* self) {
	int *variables;
	size_t recv_size_b;

	recv_size_b = sizeof(*variables) * self->_num_variables;
	variables = malloc(recv_size_b);

	socket_receive(&self->_client_socket, variables, recv_size_b);

	printf("%s\n", "Variables dump");
	for (int i = 0; i < self->_num_variables; ++i) {
		printf("%08x\n", variables[i]);
	}
}

void client_disconnect(client_t* self) {
	socket_close_connection(&self->_client_socket);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 client.c parser.c vmachine.c vars.c stack.c node.c -o testclient
// run with: ./testclient <host> <port>
