#ifndef __SERVER_H__
#define __SERVER_H__ 

#include "vmachine.h"
#include "socket.h"
#include "buffer.h"

typedef struct {
	socket_t _local_socket;
	socket_t _remote_socket;
	vmachine_t _virtual_machine;
	buffer_t _buffer;
} server_t;

// PRE:  -
// POST: Crea el socket TCP del servidor, inicia conexion del socket
// con el puerto indicado, bindeando y escuchando una conexión entrante
// En caso de error finaliza la ejecucion
void server_init(server_t* self, const char* service);

// PRE:  server inicializado con socket_init
// POST: libera recursos asociados al servidor
void server_destroy(server_t* self);

// PRE:  server inicializado con socket_init
// POST: recibe cantidad de variables para iniciar la
// maquina virtual y bytecodes para ejecutar sus instrucciones
int server_start(server_t* self);

// PRE:  self inicializado con server_init,
//		 maquina virtual inicializada
// POST: imprime por stdout el contenido de las variables de
// la maquina virtual en formato hexadecimal de ocho digitos
void server_print_variables_dump(server_t* self);

// PRE:  self inicializado con server_init,
//		 maquina virtual inicializada
// POST: envia el contenido de las variables de la maquina virtual
void server_send_variables_dump(server_t* self);

// PRE:  self inicializado con server_init
// POST: cierra socket no permitiendo envio y recepcion de datos
void server_stop(server_t* self);

#endif
