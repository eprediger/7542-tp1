#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

typedef struct node {
	int _value;	// privado
	struct node* _next;	// privado
} node_t;

// PRE:  -
// POST: el nodo self contiene el valor "value" 
// pasado por parametro y el nodo "next" en NULL
void node_init(node_t* self, int value);

// PRE:  self iniciado mediante node_init
// POST: Devuelve el valor guardado en self
int node_get_value(node_t* self);

// PRE:  self iniciado mediante node_init
// POST: Devuelve el siguiente node_t apuntado por self
node_t* node_get_next(node_t* self);

// PRE:  self iniciado mediante node_init
// POST: modifica el valor del siguiente nodo 
// apuntado, el siguiente nodo a self es next_node
void node_set_next(node_t* self, node_t* next_node);

#endif
