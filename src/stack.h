#ifndef __STACK_H__
#define __STACK_H__

#include "node.h"

typedef struct stack {
	node_t* _top;	// privado
} stack_t;

// PRE:  -
// POST: crea un stack vacío
void stack_init(stack_t* self);

// PRE:  self iniciado mediante stack_init
// POST: deja el stack vaçio liberando
// los recursos asociados a self
void stack_destroy(stack_t* self);

// PRE:  self iniciado mediante stack_init
// POST: se agrega un elemento a la pila con
// el valor val, siendo este el nuevo tope
void stack_push(stack_t* self, int val);

// PRE: self iniciado mediante stack_init,
// con al menos un elemento
// POST: se retira el último elemento ingresado a la
// pila decremetandose y retornando su valor asociado
int stack_pop(stack_t* self);

// PRE:  self iniciado mediante stack_init,
// con al menos un elemento
// POST: retorna el valor alojado en
// el tope del stack sin modificarlo
int stack_get_top(stack_t* self);

#endif
