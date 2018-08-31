#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

typedef struct node {
	int value;
	struct node* next;
} node_t;

// Devuelve una instancia de node_t
// con su dato en valor "value"
// PRE:  -
// POST: node_t apunta a un sector 
// válido de memoria.
node_t* node_init(int value);

// Libera recursos asociados a self
// PRE:  self iniciado mediante node_init
// POST: self no apunta a un sector válido
void node_destroy(node_t* self);

// Devuelve el contenido de self
// PRE:  self iniciado mediante node_init
// POST: -
int node_get_value(node_t* self);

// Devuelve el siguiente node_t apuntado por self
// PRE:  self iniciado mediante node_init
// POST: -
node_t* node_get_next(node_t* self);

// Modifica el valor del siguiente nodo apuntado
// PRE:  self iniciado mediante node_init
// POST: el siguiente nodo a self es next_node
void node_set_next(node_t* self, node_t* next_node);

#endif
