#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static void vlog_with_level(const char *level, const char *fmt, va_list args)
{
    time_t timestamp;
    struct tm tm_info;
    char date_buf[20];

    time(&timestamp);
    localtime_r(&timestamp, &tm_info);

    strftime(date_buf, sizeof(date_buf), "%Y-%m-%d %H:%M:%S", &tm_info);

    fprintf(stderr, "%s [%s] ", date_buf, level);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
}

void log_info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vlog_with_level("INFO", fmt, args);
    va_end(args);
}

void log_warn(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vlog_with_level("WARN", fmt, args);
    va_end(args);
}

void log_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vlog_with_level("ERROR", fmt, args);
    va_end(args);
}
