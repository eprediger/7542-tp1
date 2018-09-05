#ifndef __STACK_H__
#define __STACK_H__

#include "node.h"

typedef struct stack {
	node_t* _top;	// privado
} stack_t;

// Devuelve una instancia de stack_t vacía
// PRE:  -
// POST: stack_t apunta a un sector válido
void stack_init(stack_t* self);

// Libera recursos asociados a self
// PRE:  self iniciado mediante stack_init
// POST: self no apunta a un sector válido
void stack_destroy(stack_t* self);

// Incrementa el stack con el valor val
// PRE:  self iniciado mediante stack_init
// POST: se incrementa en uno el tamaño de la pila
void stack_push(stack_t* self, int val);

// Decrementa el stack y retorna el ultimo valor
// ingresado mediante stack_push
// PRE:  self iniciado mediante stack_init,
// con al menos un elemento
// POST: se decrementa en uno el tamaño de la pila
int stack_pop(stack_t* self);

// Devuelve el primer elemento del stack.
// PRE:  self iniciado mediante stack_init,
// con al menos un elemento
// POST: el stack no se modifica
int stack_get_top(stack_t* self);

/* FOR TESTING ONLY */
void stack_print(stack_t* self);

#endif
