#include "log.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* Some macros for print colorful messages to terminal. */
#define NONE                 "\e[0m"
#define RED                  "\e[0;31m"
#define GREEN                "\e[0;32m"
#define L_BLUE               "\e[1;34m"
#define L_RED                "\e[1;31m"

FILE* log_file;

void Log(LOG_LEVEL level, const char *fmt, ...){
    va_list args;
    time_t t;
    struct tm *timeinfo;

    /* Get current system time. */
    time(&t);
    timeinfo = localtime(&t);

    /* Print log prefix: notice or error. */
    if(level == NOTICE){
        fprintf(log_file, "[NOTICE]: ");
    }else if(level == WARNING){
        fprintf(log_file, "[WARNING]: ");
    }else{
        fprintf(log_file, "[ERROR]: ");
    }

    /* Show current time, such as [2012/12/12 16:58:30] */
    fprintf(log_file, "[%d/%d/%02d %02d:%02d:%02d]: ", 1900 +timeinfo->tm_year,
        1 + timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour,
        timeinfo->tm_min, timeinfo->tm_sec);

    /* Print user messages. */
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fprintf(log_file, "\n");
fflush(log_file);
    /* Error will exit program abnormally. */
    if(level == ERROR)
        exit(-1);
}

/* Do not show time version. */
#if 0
void Log(LOG_LEVEL level, const char *fmt, ...){
    va_list args;


    if(level == NOTICE){
        printf("%s[NOTICE]%s: ", GREEN, NONE);
    }else{
        printf("%s[ERROR]%s: ", RED, NONE);
    }
    
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}
#endif
