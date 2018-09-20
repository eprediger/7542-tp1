#ifndef __VMACHINE_H__
#define __VMACHINE_H__ 

#include "stack.h"
#include "vars.h"

typedef struct {
	stack_t _stack;	// privado
	var_array_t _variables;	// privado
} vmachine_t;

// PRE:  -
// POST: inicializa la instancia self de la maquina virtual, inicializando
// su stack y el arreglo de variables con dimension "variables"
void vmachine_init(vmachine_t* self, size_t variables);

// PRE:  self inicializado mediante vmachine_init
// POST: los recursos de stack y array de la máquina virtual son
// liberados y self queda en estado inválido para continuar operando
void vmachine_destroy(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// AND bit a bit y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_iand(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// OR bit a bit y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ior(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// XOR bit a bit y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ixor(vmachine_t* self);

// Retira dos elementos del stack de operandos, realiza la operación
// NOT bit a bit y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos un elemento
// POST: el tope del stack contiene el resultado de la operación.
void vmachine_ineg(vmachine_t* self);

// Retira dos elementos del stack de operandos, calcula
// la suma y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación
void vmachine_iadd(vmachine_t* self);

// Retira dos elementos del stack de operandos, calcula
// la resta y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación
void vmachine_isub(vmachine_t* self);

// Retira dos elementos del stack de operandos, calcula
// el producto y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación
void vmachine_imul(vmachine_t* self);

// Retira dos elementos del stack de operandos, calcula
// la división y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación
void vmachine_idiv(vmachine_t* self);

// Retira dos elementos del stack de operandos, calcula 
// el módulo y guarda el resultado en el mismo stack
// PRE:  stack debe tener al menos dos elementos
// POST: el tope del stack contiene el resultado de la operación
void vmachine_irem(vmachine_t* self);

// PRE:  stack debe tener al menos un elemento
// POST: duplica el último elemento del stack de operandos
// sin sacarlo y guarda la copia en el mismo stack
void vmachine_dup(vmachine_t* self);

// PRE:  self inicializado mediante vmachine_init
// POST: guarda en el stack de operandos un nuevo elementos de valor val
void vmachine_bipush(vmachine_t* self, int val);

// PRE: Los indices deben ser validos
//		0 < index < variables - 1
// POST: retira el tope del stack de operandos
// y lo guarda en la variable indexada
void vmachine_istore(vmachine_t* self, size_t index);

// PRE: Los indices deben ser validos
//		0 < index < variables - 1
// POST: toma el valor la variable indexada
// y lo guarda en el stack de operandos
void vmachine_iload(vmachine_t* self, size_t index);

// PRE:  self inicializado mediante vmachine_init
// POST: retorna el arreglo de variable de la máquina virtual
var_array_t* vmachine_get_vars(vmachine_t* self);

#endif
