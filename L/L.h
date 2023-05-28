#pragma once

#ifndef L_LIB_TAG
#define L_LIB_TAG unknown
#endif

#ifndef L_LOG_TAG
#define L_LOG_TAG unknown
#endif

#if CONFIG_LOG // hack foss: decouple zephyr

#pragma GCC diagnostic ignored "-Waddress"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(L_LOG_TAG, LOG_LEVEL_DBG);

#define L_LOGE LOG_ERR
#define L_LOGW LOG_WRN
#define L_LOGI LOG_INF
#define L_LOGD LOG_INF
// #define L_LOGE(...) (void)0
// #define L_LOGW(...) (void)0
// #define L_LOGI(...) (void)0
// #define L_LOGD(...) (void)0
#define L_LOGV(...) (void)0

#define L_LOGE_RAW LOG_RAW
#define L_LOGW_RAW LOG_RAW
#define L_LOGI_RAW LOG_RAW
#define L_LOGD_RAW LOG_RAW
#define L_LOGV_RAW LOG_RAW

#else

enum L_log_level_enum
{
    L_LOG_LEVEL_I = 'I',
    L_LOG_LEVEL_D = 'D',
    L_LOG_LEVEL_V = 'V',
    L_LOG_LEVEL_W = 'W',
    L_LOG_LEVEL_E = 'E',
};

void L_platform_log(enum L_log_level_enum level, char const *tag, char const *file, char const *line, char const *format, ...);

#define L_LOG_TOSTRING(N) L_LOG_TOSTRING2(N)
#define L_LOG_TOSTRING2(N) #N

#define L_LOG_IMPL(Level, Format, ...) \
do { \
    L_platform_log(Level, L_LOG_TOSTRING(L_LIB_TAG) "-" L_LOG_TOSTRING(L_LOG_TAG), L_LOG_TOSTRING(__FILE__), L_LOG_TOSTRING(__LINE__), Format, ##__VA_ARGS__); \
} while (0)

#if CONFIG_4ML_LOGI_DISABLE
#define L_LOGI(F, ...)
#else
#define L_LOGI(F, ...) L_LOG_IMPL(L_LOG_LEVEL_I, F, ##__VA_ARGS__)
#endif

#if CONFIG_4ML_LOGD_DISABLE
#define L_LOGD(F, ...)
#else
#define L_LOGD(F, ...) L_LOG_IMPL(L_LOG_LEVEL_D, F, ##__VA_ARGS__)
#endif

#if CONFIG_4ML_LOGV_DISABLE
#define L_LOGV(F, ...)
#else
#define L_LOGV(F, ...) L_LOG_IMPL(L_LOG_LEVEL_V, F, ##__VA_ARGS__)
#endif

#if CONFIG_4ML_LOGW_DISABLE
#define L_LOGW(F, ...)
#else
#define L_LOGW(F, ...) L_LOG_IMPL(L_LOG_LEVEL_W, F, ##__VA_ARGS__)
#endif

#if CONFIG_4ML_LOGE_DISABLE
#define L_LOGE(F, ...)
#else
#define L_LOGE(F, ...) L_LOG_IMPL(L_LOG_LEVEL_E, F, ##__VA_ARGS__)
#endif

#ifdef L_IMPL

#if CONFIG_L_PLATFORM_POSIX

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#define L_LOG_STREAM stdout
#define L_LOG_ERROR_STREAM stderr

static unsigned long wallclock_ms(void) 
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000UL + ts.tv_nsec / 1000000UL;
}

// #pragma GCC diagnostic ignored "-Wpedantic" // todo crz: do we need this for non-literal format?

void L_platform_log(enum L_log_level_enum level, char const *tag, char const *file, char const *line, char const *format, ...)
{
    FILE *stream = L_LOG_STREAM;

    if (L_LOG_LEVEL_E == level || L_LOG_LEVEL_W == level)
    {
        stream = L_LOG_ERROR_STREAM;
    }

    fprintf(stream, "%lu %c/%s(): ", wallclock_ms(), level, tag);

    va_list args;
    va_start(args, format);

    vfprintf(stream, format, args);

    va_end(args);

    if (file)
    {
        fprintf(stream, " [%s:%s]", file, line);
    }

    fprintf(stream, "\n");

    fflush(stream);
}

#else

void L_platform_log(enum L_log_level_enum level, char const *tag, char const *file, char const *line, char const *format, ...)
{
}


//#error L not supported on this platform

#endif

#endif

#endif