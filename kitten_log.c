#include "kitten_log.h"

void kitten_log(enum kitten_log_level level, const char *tag, const char *format, ...)
{
    char log_buffer[KITTEN_LOG_BUF_SIZE];
    unsigned int offset = 0;
    
    const char *level_color = NULL;
    const char *level_str = NULL;

    switch(level){
        case KITTEN_LOG_LEVEL_DEBUG:
            level_color = "\033[36m"; // Cyan
            level_str = "D";
            break;
        case KITTEN_LOG_LEVEL_INFO:
            level_color = "\033[32m"; // Green
            level_str = "I";
            break;
        case KITTEN_LOG_LEVEL_WARN:
            level_color = "\033[33m"; // Yellow
            level_str = "W";
            break;
        case KITTEN_LOG_LEVEL_ERROR:
            level_color = "\033[31m"; // Red
            level_str = "E";
            break;
    }

#ifdef KITTEN_LOG_TIME
    uint32_t time_ms = platform_kitten_log_get_time_ms();
    #if defined(KITTEN_LOG_TIME_MS)
    offset += snprintf(log_buffer + offset,
                       sizeof(log_buffer) - offset,
                       "%s[%010lu][%s][%s]: ",
                       level_color,time_ms,level_str,tag);
    #elif defined(KITTEN_LOG_TIME_S)
    offset += snprintf(log_buffer + offset,
                       sizeof(log_buffer) - offset,
                       "%s[%06lu.%03lu][%s][%s]: ",
                       level_color,time_ms / 1000U, time_ms % 1000U, level_str,tag);
    #endif
#else
    offset += snprintf(log_buffer + offset,
                       sizeof(log_buffer) - offset,
                       "%s[%s][%s]: ",
                       level_color,level_str,tag);
#endif
    
    va_list args;
    va_start(args, format);
    offset += vsnprintf(log_buffer + offset,
                        sizeof(log_buffer) - offset,
                        format,
                        args);
    va_end(args);

    snprintf(log_buffer + offset,
             sizeof(log_buffer) - offset,
             "\033[0m\r\n");

    platform_kitten_log_print(log_buffer, strlen(log_buffer));
}