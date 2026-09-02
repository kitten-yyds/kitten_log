#ifndef KITTEN_LOG_H
#define KITTEN_LOG_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#if defined(KITTEN_LOG_TIME)
    #if defined(KITTEN_LOG_TIME_S) && defined(KITTEN_LOG_TIME_MS)
        #error KITTEN_LOG_TIME_S and KITTEN_LOG_TIME_MS cannot both be defined.
    #endif
    #if !defined(KITTEN_LOG_TIME_S) && !defined(KITTEN_LOG_TIME_MS)
        #error either macro A or macro B needs to be defined
    #endif
#endif

#ifdef KITTEN_LOG_TIME
uint32_t platform_kitten_log_get_time_ms();
#endif
void platform_kitten_log_print(const char *text, unsigned int length);

#define KITTEN_LOG_BUF_SIZE 256

#define KITTEN_LOGD(tag, format, ...) kitten_log(KITTEN_LOG_LEVEL_DEBUG, tag, format, ##__VA_ARGS__)
#define KITTEN_LOGI(tag, format, ...) kitten_log(KITTEN_LOG_LEVEL_INFO, tag, format, ##__VA_ARGS__)
#define KITTEN_LOGW(tag, format, ...) kitten_log(KITTEN_LOG_LEVEL_WARN, tag, format, ##__VA_ARGS__)
#define KITTEN_LOGE(tag, format, ...) kitten_log(KITTEN_LOG_LEVEL_ERROR, tag, format, ##__VA_ARGS__)

enum kitten_log_level{
    KITTEN_LOG_LEVEL_DEBUG,
    KITTEN_LOG_LEVEL_INFO,
    KITTEN_LOG_LEVEL_WARN,
    KITTEN_LOG_LEVEL_ERROR
};

void kitten_log(enum kitten_log_level level, const char *tag, const char *format, ...);

#endif