#ifndef __VMACHINE_H__
#define __VMACHINE_H__ 

#include "stack.h"
#include "vars.h"

typedef struct {
	stack_t* stack;
	var_array_t* variables;
} vmachine_t;

// Inicializa la máquina virtual en un estado válido
// PRE:  -
// POST: vmachine_t* apunta a un sector válido
vmachine_t* vmachine_init(int variables);

// Libera los recursos asociados a la máquina virtual
// PRE:  self inicializado mediante vmachine_init
// POST: los recursos de pila y array de la máquina virtual son
// liberados y self queda en estado inválido para continuar operando
void vmachine_destroy(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// AND bit a bit y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_iand(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// OR bit a bit y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ior(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// XOR bit a bit y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ixor(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// NOT bit a bit y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos un valor
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ineg(vmachine_t* self);

// Retira dos elementos del stack del operando, calcula
// la suma y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación
void vmachine_iadd(vmachine_t* self);

// Retira dos elementos del stack del operando, calcula
// la resta y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación
void vmachine_isub(vmachine_t* self);

// Retira dos elementos del stack del operando, calcula
// la multiplicación y guarda el resultado en el mismo .stack
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación
void vmachine_imul(vmachine_t* self);

// Retira dos elementos del stack del operando, calcula
// la división y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación
void vmachine_idiv(vmachine_t* self);

// Retira dos elementos del stack del operando, calcula 
// el módulo y guarda el resultado en el mismo stack.
// PRE:  stack debe tener al menos dos valores.
// POST: el tope del stack contiene el resultado de la operación
void vmachine_irem(vmachine_t* self);

// duplica el último elemento del stack de operando 
// sin sacarlo y guarda la copia en el mismo stack
// PRE:  
// POST: 
void vmachine_dup(vmachine_t* self);

// lee el siguiente byte code, lo extiende a un
// int con signo y lo guarda en el stack de operandos
// PRE:  
// POST: 
void vmachine_bipush(vmachine_t* self, int val);

// Retira un elemento del stack de operandos y lo guarda en
// la variable indexada.
// PRE: Se garantiza que los indices son válidos
// POST: 
void vmachine_istore(vmachine_t* self, unsigned int index);

// Lee la variable indexada y la guarda en el stack 
// de operandos.
// PRE: Se garantiza que los indices son válidos
// POST: 
void vmachine_iload(vmachine_t* self, unsigned int index);

/* FOR TESTING ONLY */
// void vmachine_print_stack(vmachine_t* self);

void vmachine_print_vars(vmachine_t* self);

#endif
