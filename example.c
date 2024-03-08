#include <assert.h>

#include "barectf-platform-linux-fs.h"
#include "barectf.h"

int main(void)
{
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