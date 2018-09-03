// #include "client.h"
// #include "server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_ARGS 2
#define SERVER_ARGS 3
#define CLIENT_MIN_ARGS 4
#define CLIENT_MAX_ARGS 5

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 tp1.c -o testtp
// run with: ./testtp <user> <host> <port> [<filename>]

int main(int argc, const char *argv[]) {
	server_t* servidor;
	client_t* cliente;

	if (argc >= MIN_ARGS) {
		const char* nombre_serv = "server";
		const char* nombre_cli  = "client";

		if (strncmp(argv[1], nombre_serv, strlen(argv[1])) == 0) {
			if (argc != SERVER_ARGS) {
				fprintf(stderr, "Usage: %s %s <port>\n", argv[0], argv[1]);
				exit(EXIT_FAILURE);
			} else {
				// Aca empieza el server
				servidor = server_init(argv[2]);	// argv[2] = <port>
				server_start(servidor);
				server_send_variables_dump(servidor);
				// server_stop(servidor);
				// server_destroy(servidor);
			}
		} else if (strncmp(argv[1], nombre_cli, strlen(argv[1])) == 0) {
			if ((argc != CLIENT_MIN_ARGS) && (argc != CLIENT_MAX_ARGS)) {
				fprintf(stderr, "Usage: %s %s <host> <port> <num-vars> [<filename>]\n", argv[0], argv[1]);
				exit(EXIT_FAILURE);
			} else {
				// Aca empieza el client
				const int num_variables = atoi(argv[4]);
				if (argc == CLIENT_MIN_ARGS) {
					cliente = client_init(NULL, num_variables);		// Se leera de standard input
				} else {
					cliente = client_init(argv[5], num_variables);	// argv[5] = <filename>
				}
				client_connect(cliente, argv[2], argv[3]);	// argv[2] = <host> | argv[3] = port
				client_send_vars_size(cliente, argv[4]);	// argv[4] = <num-vars>
				client_send_bytecodes(cliente);
				client_receive_variable_dump(cliente);
				client_disconnect(cliente);
				client_destroy(cliente);
			}
		}
	} else {
		fprintf(stderr, "%s: Error de invocación\n", argv[0]);
		fprintf(stderr, "Modo cliente:\t%s client <host> <port> [<filename>]\n", argv[0]);
		fprintf(stderr, "Modo servidor:\t%s server <port>\n", argv[0]);
	}

	return EXIT_SUCCESS;
}
