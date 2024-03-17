#include <assert.h>

#include "barectf-platform-linux-fs.h"
#include "barectf.h"
#include "zmq_api.h"

int main(void)
{
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
    struct barectf_platform_linux_fs_ctx *platform_ctx;
    struct barectf_default_ctx *barectf_ctx;
    unsigned int i;

    platform_ctx = barectf_platform_linux_fs_init(256, "trace/stream",
                                                  0, 0, 0);
    assert(platform_ctx);
    barectf_ctx = barectf_platform_linux_fs_get_barectf_ctx(platform_ctx);

    for (i = 0; i < 50; ++i) {
        barectf_trace_my_event(barectf_ctx, i);
    }

    barectf_platform_linux_fs_fini(platform_ctx);
    return 0;
}