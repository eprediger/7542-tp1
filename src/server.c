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
#define IAND	0x7E
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

void server_init(server_t* self, const char* service) {
	int init_error = 0;
	socket_init(&self->_local_socket, NULL, service, AI_PASSIVE);
	buffer_init(&self->_buffer);
	if (init_error != 0) {
		
	}
}

void server_destroy(server_t* self) {
	socket_destroy(&(self->_local_socket));
	vmachine_destroy(&(self->_virtual_machine));
	buffer_destroy(&(self->_buffer));
}

static void server_nto_bufl(int* data, int data_size) {
	for (int i = 0; i < data_size; ++i) {
		data[i] = ntohl(data[i]);
	}
}

static void run_vm_instructions(vmachine_t* vm, int* bytecodes, int size) {
	printf("%s\n", "Bytecode trace");
	for (int i = 0; i < size; ++i) {
		int bytecode = bytecodes[i];
		switch (bytecode) {
			case IAND:
				vmachine_iand(vm);
				break;
			case IOR:
				vmachine_ior(vm);
				break;
			case IXOR:
				vmachine_ixor(vm);
				break;
			case INEG:
				vmachine_ineg(vm);
				break;
			case IADD:
				vmachine_iadd(vm);
				break;
			case ISUB:
				vmachine_isub(vm);
				break;
			case IMUL:
				vmachine_imul(vm);
				break;
			case IDIV:
				vmachine_idiv(vm);
				break;
			case IREM:
				vmachine_irem(vm);
				break;
			case DUP:
				vmachine_dup(vm);
				break;
			case BIPUSH:
				i++;
				bytecode = bytecodes[i];
				vmachine_bipush(vm, bytecode);
				break;
			case ISTORE:
				i++;
				bytecode = bytecodes[i];
				vmachine_istore(vm, bytecode);
				break;
			case ILOAD:
				i++;
				bytecode = bytecodes[i];
				vmachine_iload(vm, bytecode);
				break;
		}
	}
}

void server_print_variables_dump(server_t* self) {
	var_array_t* variables_dump = vmachine_get_vars(&self->_virtual_machine);
	size_t array_size = vars_get_array_size(variables_dump);

	printf("\n%s\n", "Variables dump");
	for (int i = 0; i < array_size; ++i) {
		printf("%08x\n", vars_get_variable_by_index(variables_dump, i));
	}
}

int server_start(server_t* self) {
	bool running = true;
	
	socket_bind(&self->_local_socket);
	socket_listen(&self->_local_socket, MAX_LISTEN);
	socket_accept(&self->_local_socket, &self->_remote_socket);

	//	Recibo numero de variables, se lanza VM
	int vm_vars = 0;
	socket_receive(&self->_remote_socket, &vm_vars, sizeof(vm_vars));
	vm_vars = ntohl(vm_vars);
	vmachine_init(&self->_virtual_machine, vm_vars);

	int* buf_recv;
	size_t max_recv = buffer_get_max_size(&self->_buffer);
	size_t max_recv_b = sizeof(*buf_recv) * max_recv;
	buf_recv = buffer_get_transformed_data(&self->_buffer);
	
	//	Recibo bytecodes
	while (running) {
		int received = 0;
		buffer_reset(&self->_buffer);

		received = socket_receive(&self->_remote_socket, buf_recv, max_recv_b);

		running = (received > 0);
		
		if (running) {
			int total_instr = received/sizeof(*buf_recv);
			server_nto_bufl(buf_recv, total_instr);
			run_vm_instructions(&self->_virtual_machine, buf_recv, total_instr);
		}
	}
	server_print_variables_dump(self);

	return 0;
}

static void server_buf_tonl(int* data, int data_size) {
	for (int i = 0; i < data_size; ++i) {
		data[i] = htonl(data[i]);
	}
}

void server_send_variables_dump(server_t* self) {
	var_array_t* variables_dump = vmachine_get_vars(&self->_virtual_machine);

	int* vars = vars_get_array(variables_dump);
	size_t vars_size = vars_get_array_size(variables_dump);
	
	size_t send_size_b = sizeof(*vars) * vars_size;
	
	server_buf_tonl(vars, vars_size);
	
	socket_send(&self->_remote_socket, &vars[0], send_size_b);
}

void server_stop(server_t* self) {
	socket_close_connection(&self->_local_socket);
	socket_close_connection(&self->_remote_socket);
}
