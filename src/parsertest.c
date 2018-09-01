#include "vmachine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 1
#define VARIABLES_VM 4

#define IAND	0x7e
#define IOR		0x80
#define IXOR	0x82
#define INEG	0x74

#define IADD	0x60
#define ISUB	0x64
#define IMUL	0x68
#define IDIV	0x6c
#define IREM	0x70

#define DUP		0x59
#define BIPUSH	0x10

#define ISTORE	0x36
#define ILOAD	0x15

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 parsertest.c vmachine.c vars.c stack.c node.c -o parsertest
// run with: ./parsertest <filename>

void get_bytecode(FILE* file, unsigned char* bytecode) {
	fread((char*)bytecode, sizeof(*bytecode), COUNT, file);
}

int main(int argc, const char *argv[]) {
	vmachine_t* jvm = vmachine_init(VARIABLES_VM);
	
	FILE* file;
	unsigned char bytecode = 0;

	if (argc == 1) {
		file = stdin;
	} else {
		file = fopen(argv[1], "rb");
	}

	printf("%s\n", "Bytecode trace");
	while(!feof(file)) {
		get_bytecode(file, &bytecode);
		switch (bytecode) {
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
				get_bytecode(file, &bytecode);
				vmachine_bipush(jvm, bytecode);
				break;
			case ISTORE:
				get_bytecode(file, &bytecode);
				vmachine_istore(jvm, bytecode);
				break;
			case ILOAD:
				get_bytecode(file, &bytecode);
				vmachine_iload(jvm, bytecode);
				break;
		}
	}	

	printf("\n");

	if (argc == 2) {
		fclose(file);
	}

	// vmachine_print_stack(jvm);
	vmachine_print_vars(jvm);

	vmachine_destroy(jvm);
	
	return 0;
}