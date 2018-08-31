/* 
 * imprimir por salida estándar el contenido del array de variables imprimiendo
 * cada número en su propia línea en notación hexadecimal de 8 dígitos.
 */

#include <stdio.h>
#include <stdlib.h>

/* 
 * compile with: gcc -Wall -Werror -std=c99 -pedantic -O0 testprint.c -o testprint
 * run with: ./testprint <array-size>
 */

int main(int argc, char const *argv[]) {
	int elem = atoi(argv[1]);
	int array[elem];

	printf("Queres %d elementos\n", elem);

	for (int i = 0; i < elem; ++i) {
		printf("Dame un numero: ");
		scanf("%d", &array[i]);
	}

	//	Imprime número en hexa llenando
	//	con 0's hasta ocho dígitios
	for (int i = 0; i < elem; ++i) 	{
		printf("Elemento %d: %08x\n", i, array[i]);
	}

	return 0;
}
