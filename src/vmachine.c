#include "vmachine.h"

#include "stack.h"
#include "vars.h"

#include <stdlib.h>
#include <stdio.h>

//	"Variables dump\n"
#define VAR_DUMP_MSG_SIZE 15
//	"00000000\n"
#define VAR_PRINT_SIZE 9

void vmachine_init(vmachine_t* self, int variables) {
	stack_init(&self->_stack);
	vars_init(&self->_variables, variables);
}

void vmachine_destroy(vmachine_t* self) {
	vars_destroy(&self->_variables);
	stack_destroy(&self->_stack);
}

void vmachine_iand(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a & b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "iand");
}

void vmachine_ior(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a | b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "ior");
}

void vmachine_ixor(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a ^ b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "ixor");
}

void vmachine_ineg(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int result = ~a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "ineg");
}

void vmachine_iadd(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a + b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "iadd");
}

void vmachine_isub(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a - b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "isub");
}

void vmachine_imul(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a * b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "imul");
}

void vmachine_idiv(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a / b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "idiv");
}

void vmachine_irem(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = a % b;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "irem");
}

void vmachine_dup(vmachine_t* self) {
	stack_push(&self->_stack, stack_get_top(&self->_stack));
	fprintf(stdout, "%s\n", "dup");
}

void vmachine_bipush(vmachine_t* self, int val) {
	stack_push(&self->_stack, val);
	fprintf(stdout, "%s\n", "bipush");
}

void vmachine_istore(vmachine_t* self, unsigned int index) {
	vars_set_variable_by_index(&self->_variables, index, stack_pop(&self->_stack));
	fprintf(stdout, "%s\n", "istore");
}

void vmachine_iload(vmachine_t* self, unsigned int index) {
	stack_push(&self->_stack, vars_get_variable_by_index(&self->_variables, index));
	fprintf(stdout, "%s\n", "iload");
}

char* vmachine_get_vars(vmachine_t* self) {
	unsigned int len_variable_dump = VAR_DUMP_MSG_SIZE;
	unsigned int array_size = vars_get_array_size(&self->_variables);
	
	len_variable_dump += (array_size * VAR_PRINT_SIZE);
	char* variable_dump = malloc(sizeof(char) * (len_variable_dump + 1));	// '\0'

	unsigned int current_pos = 0;
	current_pos = snprintf(variable_dump, VAR_DUMP_MSG_SIZE, "%s", "Variables dump\n");

	for (unsigned i = 0; i < array_size; ++i) {
		int var_val = vars_get_variable_by_index(&self->_variables, i);
		char* s = &variable_dump[current_pos];
		current_pos += snprintf(s, VAR_PRINT_SIZE, "%08x\n", var_val);
	}

	return variable_dump;
}

/* FOR TESTING ONLY */
void vmachine_print_stack(vmachine_t* self) {
	stack_print(&self->_stack);
}

void vmachine_print_vars(vmachine_t* self) {
	vars_print_vars_with_format(&self->_variables);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 vmachine.c vars.c stack.c node.c -o ../test/testvmachine
// run with: ../test/testvmachine <num-vars>

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./vmachinetest <num-vars>\n");
		return 1;
	}
	
	vmachine_t jvm;
	vmachine_init(&jvm, atoi(argv[1]));

	printf("Bytecode trace\n");
	vmachine_bipush(&jvm, 0x41);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);
	
	vmachine_dup(&jvm);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_dup(&jvm);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_istore(&jvm, 0x00);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_bipush(&jvm, 0x01);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_iadd(&jvm);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_dup(&jvm);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_dup(&jvm);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_istore(&jvm, 0x01);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	// vmachine_istore(&jvm, 0x02);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	// vmachine_iload(&jvm, 0x03);
	// vmachine_print_stack(&jvm);
	// vmachine_print_vars(&jvm);

	vmachine_print_vars(&jvm);

	/*printf("Test AND\n");
	vmachine_bipush(&jvm, 0xC8);
	vmachine_bipush(&jvm, 0xB8);
	vmachine_iand(&jvm);
	vmachine_print_stack(&jvm);
	vmachine_get_vars(&jvm);

	printf("Test OR\n");
	vmachine_bipush(&jvm, 0xC8);
	vmachine_bipush(&jvm, 0xB8);
	vmachine_ior(&jvm);
	vmachine_print_stack(&jvm);
	vmachine_get_vars(&jvm);
	
	printf("Test XOR\n");
	vmachine_bipush(&jvm, 0xC8);
	vmachine_bipush(&jvm, 0xB8);
	vmachine_ixor(&jvm);
	vmachine_print_stack(&jvm);
	vmachine_get_vars(&jvm);

	printf("Test NEG\n");
	vmachine_bipush(&jvm, 0xC8);
	vmachine_ineg(&jvm);
	vmachine_print_stack(&jvm);
	vmachine_get_vars(&jvm);*/

	vmachine_destroy(&jvm);
	return 0;
}
