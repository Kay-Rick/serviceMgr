#ifndef __LOG_H
#define __LOG_H

#include <stdarg.h>
#include <stdio.h>

typedef enum LOG_LEVEL{
    NOTICE,
    WARNING,
    ERROR
}LOG_LEVEL;

extern FILE* log_file;
void Log(LOG_LEVEL level, const char *fmt, ...);

#endif
