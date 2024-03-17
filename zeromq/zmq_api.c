
#include "zmq_api.h"

void *context = NULL;
void *data_socket = NULL;
const char *TOPIC = "Trace";
const char *TCP = "tcp://*:5555";
size_t topic_size = sizeof(TOPIC);

zmq_connection_return_values zmq_api_init(){
    context = zmq_ctx_new();

    if (!context)
    {
        // printf("ERROR: ZeroMQ error occurred during zmq_ctx_new(): %s\n", zmq_strerror(errno));
        return E_ERROR_CONTEXT;
    }
    data_socket = zmq_socket(context, ZMQ_PUB);
    const int rb = zmq_bind(data_socket, TCP);
    sleep(1);
    if (rb != 0)
    {
        // printf("ERROR: ZeroMQ error occurred during zmq_ctx_new(): %s\n", zmq_strerror(errno));
        return E_ERROR_BINDING;
    }
    return E_OK;
}

zmq_connection_return_values zmq_api_send_mess(int mess_size, int* buffer){

    size_t envelope_size = topic_size + 1 + mess_size * sizeof(int);
    zmq_msg_t envelope;
    const int rmi = zmq_msg_init_size(&envelope, envelope_size);

    if (rmi != 0)
    {
        // printf("ERROR: ZeroMQ error occurred during zmq_msg_init_size(): %s\n", zmq_strerror(errno));
        zmq_msg_close(&envelope);
        return E_ERROR_INIT_SIZE;
    }

    memcpy(zmq_msg_data(&envelope), TOPIC, topic_size);
    memcpy((void*)((char*)zmq_msg_data(&envelope) + topic_size), " ", 1);
    memcpy((void*)((char*)zmq_msg_data(&envelope) + (1 + topic_size)), buffer, mess_size * sizeof(int));

    const size_t rs = zmq_msg_send(&envelope, data_socket, 0);
    if (rs != envelope_size)
    {
        // printf("ERROR: ZeroMQ error occurred during zmq_msg_send(): %s\n", zmq_strerror(errno));
        zmq_msg_close(&envelope);
        return E_ERROR_SEND_MESS;
    }

    zmq_msg_close(&envelope);
    printf("Message sent; data: %u\n", buffer[0]);
    sleep(1);
    return E_OK;
}
zmq_connection_return_values zmq_api_close(){
    const int rc = zmq_close(data_socket);
    if (rc != 0)
    {
        // printf("ERROR: ZeroMQ error occurred during zmq_close(): %s\n", zmq_strerror(errno));
        return E_ERROR_CLOSE_CONNECTION;
    }

    const int rd = zmq_ctx_destroy(context);

    if (rd != 0)
    {
        // printf("Error occurred during zmq_ctx_destroy(): %s\n", zmq_strerror(errno));
        return E_ERROR_DESTROY_CONTEXT;
    }
    return E_OK;
}
