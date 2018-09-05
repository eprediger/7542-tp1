#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void node_init(node_t* self, int value) {
	self->_value = value;
	self->_next = NULL;
}

void node_destroy(node_t* self) { }

int node_get_value(node_t* self) {
	return self->_value;
}

node_t* node_get_next(node_t* self) {
	return self->_next;
}

void node_set_next(node_t* self, node_t* next_node) {
	self->_next = next_node;
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 node.c -o ../test/testnodo
// run with: ../test/testnodo <num1> <num2>

/*int main(int argc, const char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./nodotest <num1> <num2>\n");
		return 1;
	}

	int valor = atoi(argv[1]);	//strtol(argv[1], NULL, 10);
	node_t nodo;
	node_init(&nodo, valor);

	int otro_valor = atoi(argv[2]);
	node_t otro_nodo;
	node_init(&otro_nodo, otro_valor);
	node_set_next(&nodo, &otro_nodo);

	printf("El valor en nodo es: %d\n", node_get_value(&nodo));

	printf("El valor en otro_nodo es: %d\n", node_get_value(&otro_nodo));

	printf("Desde nodo, otro_nodo vale: %d\n", node_get_value(node_get_next(&nodo)));

	node_destroy(&nodo);
	node_destroy(&otro_nodo);
	return 0;
}*/
