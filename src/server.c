#define _POSIX_C_SOURCE 200112L

#include "server.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

// Virtual Machine Bytecodes
#define IAND	0X7E
#define IOR		0x80
#define IXOR	0x82
#define INEG	0x74

#define IADD	0x60
#define ISUB	0x64
#define IMUL	0x68
#define IDIV	0x6C
#define IREM	0x70

#define DUP		0x59
#define BIPUSH	0x10

#define ISTORE	0x36
#define ILOAD	0x15

#define MAX_LISTEN 1
#define MESSAGE_SIZE 2

server_t* server_init(const char* service) {
	server_t* self = malloc(sizeof(server_t));
	
	self->remote_socket = malloc(sizeof(socket_t));

	self->local_socket = socket_init(NULL, service, AI_PASSIVE);

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
	// int error_code = 0;
	
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
		
		switch ((unsigned char)message[0]) {
			case IAND:
				vmachine_iand(self->virtual_machine);
				break;
			case IOR:
				vmachine_ior(self->virtual_machine);
				break;
			case IXOR:
				vmachine_ixor(self->virtual_machine);
				break;
			case INEG:
				vmachine_ineg(self->virtual_machine);
				break;
			case IADD:
				vmachine_iadd(self->virtual_machine);
				break;
			case ISUB:
				vmachine_isub(self->virtual_machine);
				break;
			case IMUL:
				vmachine_imul(self->virtual_machine);
				break;
			case IDIV:
				vmachine_idiv(self->virtual_machine);
				break;
			case IREM:
				vmachine_irem(self->virtual_machine);
				break;
			case DUP:
				vmachine_dup(self->virtual_machine);
				break;
			case BIPUSH:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_bipush(self->virtual_machine, message[1]);
				break;
			case ISTORE:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_istore(self->virtual_machine, message[1]);
				break;
			case ILOAD:
				socket_receive(self->remote_socket, message, MESSAGE_SIZE - 1);
				vmachine_iload(self->virtual_machine, message[1]);
				break;
		}

		running = (message[0] != '\0');
	}
}

void server_print_variables_dump(server_t* self) {
	char* variables_dump = vmachine_get_vars(self->virtual_machine);

	fprintf(stdout, "%s", variables_dump);

	free(variables_dump);
}

void server_send_variables_dump(server_t* self) {
	char* variables_dump = vmachine_get_vars(self->virtual_machine);
	
	socket_send(self->local_socket, variables_dump, strlen(variables_dump));

	free(variables_dump);
}

void server_stop(server_t* self) {
	socket_close_connection(self->local_socket);
	socket_close_connection(self->remote_socket);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 server.c parser.c vmachine.c vars.c stack.c node.c -o testserver
// run with: ./testserver <host> <port>
