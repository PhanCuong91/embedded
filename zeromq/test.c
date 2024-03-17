#include "zmq_api.h"
// For printf()
#include <stdio.h>

int main(void)
{
    const unsigned int INIT_PARAM = 12345;
    const unsigned int REPETITIONS = 10;
    const unsigned int PACKET_SIZE = 16;
    const char *TOPIC = "fancyhw_data";
    void *data_socket = NULL;
    void *context = NULL;
    zmq_connection_return_values rs = zmq_api_init();
    if (rs != E_OK){
        printf("initialization is not okay");
        return 0;
    }
    const int t_size = 2;
    int buffer[t_size];
    for(int i=0; i<10 ; i++){
        buffer[0] = i+2;
        buffer[1] = i+1;
        zmq_api_send_mess(t_size,buffer);
    }
    zmq_api_close();
    return 1;

}