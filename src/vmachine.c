#include "vmachine.h"

#include "stack.h"
#include "vars.h"

#include <stdlib.h>
#include <stdio.h>

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
	int result = -a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "ineg");
}

void vmachine_iadd(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = b + a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "iadd");
}

void vmachine_isub(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = b - a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "isub");
}

void vmachine_imul(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = b * a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "imul");
}

void vmachine_idiv(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = b / a;
	stack_push(&self->_stack, result);
	fprintf(stdout, "%s\n", "idiv");
}

void vmachine_irem(vmachine_t* self) {
	int a = stack_pop(&self->_stack);
	int b = stack_pop(&self->_stack);
	int result = b % a;
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

void vmachine_istore(vmachine_t* self, size_t index) {
	int popped_item = stack_pop(&self->_stack);
	vars_set_variable_by_index(&self->_variables, index, popped_item);
	fprintf(stdout, "%s\n", "istore");
}

void vmachine_iload(vmachine_t* self, size_t index) {
	int reg_val = vars_get_variable_by_index(&self->_variables, index);
	stack_push(&self->_stack, reg_val);
	fprintf(stdout, "%s\n", "iload");
}

var_array_t* vmachine_get_vars(vmachine_t* self) {
	return &self->_variables;
}
