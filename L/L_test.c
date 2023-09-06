#ifdef ONELETTER_TEST

#include <stdio.h>

#define L_LIB_TAG LLIB
#define L_LOG_TAG LLOG
#define CONFIG_L_PLATFORM_POSIX 1

#define L_IMPL
#include "L.h"

int main()
{
    L_LOGV("log V");
    L_LOGD("log D");
    L_LOGI("log I");
    L_LOGW("log W");
    L_LOGE("log E");

    return 0;
}

#endif
