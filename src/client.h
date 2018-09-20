#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "socket.h"
#include "parser.h"
#include "vars.h"

typedef struct {
	socket_t _client_socket;	// privado
	parser_t _parser;	// privado
	int _num_variables;	// privado
} client_t;

// PRE:  file debe ser una ruta a un archivo válida
// o NULL si la entrada será la standard, variables > 0
// POST: Inicializa para la conexión al servidor
void client_init(client_t* self, const char* file, const int variables);

// PRE:  self inicializado mediante client_init
// POST: libera los recursos asociados a self
void client_destroy(client_t* self);

// PRE:  self inicializado mediante client_init
// POST: inicializa la conexión vía socket TCP hacia host, IP o URL, y
// service, numero de puerto o servicio, en caso de error finaliza la ejecución
void client_connect(client_t* self, const char* host, const char* service);

// PRE:  self inicializado mediante client_init y conectado vía client_connect
// POST: envía al servidor vía el socket TCP creado el
// numero de variables solicitado para la maquina virtual
void client_send_vars_size(client_t* self, const char* num_variables);

// PRE:  self inicializado mediante client_init y conectado vía client_connect
// POST: envía vía socket TCP los bytecodes leídos de entrada
// estandar o archivo pasado por parametro. Una vez finalizado
// el envio cierra el canal de escritura del socket
void client_send_bytecodes(client_t* self);

// PRE:  self inicializado mediante client_init y conectado vía client_connect
// POST: recibe vía socket el contenido de las variables de la maquina virtual
// e imprime sus valores por stdout en notación hexadecimal de 8 digitos
void client_receive_variable_dump(client_t* self);

// PRE:  self inicializado mediante client_init y conectado vía client_connect
// POST: cierra la conexion del socket tanto para lectura como escritura
void client_disconnect(client_t* self);

#endif
