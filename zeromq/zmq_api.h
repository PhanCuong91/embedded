#ifndef ZQM_API_H
#define ZQM_API_H

#include <zmq.h>
// For memcpy()
#include <string.h>
// For sleep()
#include <unistd.h>
// For printf()
#include <stdio.h>
// For EXIT_*
#include <stdlib.h>

typedef enum zmq_connection_return_values{
    E_OK,
    E_ERROR_CONTEXT,
    E_ERROR_BINDING,
    E_ERROR_INIT_SIZE,
    E_ERROR_SEND_MESS,
    E_ERROR_CLOSE_CONNECTION,
    E_ERROR_DESTROY_CONTEXT
} zmq_connection_return_values;

zmq_connection_return_values zmq_api_init();
zmq_connection_return_values zmq_api_send_mess(int mess_size, int* buffer);
zmq_connection_return_values zmq_api_close();

#endif /*ZQM_API_H*/