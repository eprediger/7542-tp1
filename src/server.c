#include "server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

#define MAX_LISTEN 1
#define MESSAGE_SIZE 2

server_t* server_init(const char* service) {
	server_t* self = malloc(sizeof(server_t));
	
	self->remote_socket = socket_create();

	int s = 0;
	struct addrinfo hints;
	struct addrinfo* result;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // Server

	s = getaddrinfo(NULL, service, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	self->local_socket = socket_init(result);

	freeaddrinfo(result);

	return self;
}

void server_destroy(server_t* self) {
	socket_destroy(self->local_socket);
	socket_destroy(self->remote_socket);
	vmachine_destroy(self->virtual_machine);
	free(self);
}

void server_start(server_t* self) {
	bool running = true;
	int error_code = 0;
	
	socket_bind(self->local_socket);
	socket_listen(self->local_socket, MAX_LISTEN);
	socket_accept(self->local_socket, self->remote_socket);

	//	Recibo numero de variables
	char message[MESSAGE_SIZE];
	memset(message, 0, MESSAGE_SIZE);	
	socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);

	self->virtual_machine = vmachine_init(atoi(message));

	//	Recibo bytecodes
	while (running) {
		memset(message, 0, MESSAGE_SIZE);
		socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
		
		switch (message[0]) {
			case IAND:
				vmachine_iand(jvm);
				break;
			case IOR:
				vmachine_ior(jvm);
				break;
			case IXOR:
				vmachine_ixor(jvm);
				break;
			case INEG:
				vmachine_ineg(jvm);
				break;
			case IADD:
				vmachine_iadd(jvm);
				break;
			case ISUB:
				vmachine_isub(jvm);
				break;
			case IMUL:
				vmachine_imul(jvm);
				break;
			case IDIV:
				vmachine_idiv(jvm);
				break;
			case IREM:
				vmachine_irem(jvm);
				break;
			case DUP:
				vmachine_dup(jvm);
				break;
			case BIPUSH:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_bipush(jvm, message[0]);
				break;
			case ISTORE:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_istore(jvm, message[0]);
				break;
			case ILOAD:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_iload(jvm, bytecode);
				break;
		}

		running = ((int)(message[0]) != EOF);
	}

	vmachine_print_vars(server->virtual_machine);
}

void server_send_variables_dump(server_t* self) {

}

void server_stop(server_t* self) {
	socket_close_connection(self->local_socket);
	socket_close_connection(self->remote_socket);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 server.c parser.c vmachine.c vars.c stack.c node.c -o testserver
// run with: ./testserver <host> <port>
