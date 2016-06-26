//
// Created by barrauh on 6/26/16.
//

#include "Generic.h"

extern uint64_t on_heap;

static inline string GetCurrentTime() {
    char *ret = xmalloc(sizeof(char) * 50);
    time_t t = time(NULL);
    struct tm * p = localtime(&t);
    strftime(ret, 50, "%d/%m/%y : %T", p);
    return ret;
}

static inline string GetCurrentUsage() {
    int sizeInByte;

    sizeInByte = (int)((double)(on_heap * CHAR_BIT) / 8);
    if (sizeInByte < 1)
        return asprintf("MEM : %d b", (int) (on_heap * CHAR_BIT));
    if (sizeInByte < 1024)
        return asprintf("MEM : %d B", sizeInByte);
    else if (sizeInByte > 1024 && sizeInByte < 1048576)
        return asprintf("MEM : %.3f KB", (float)sizeInByte / (float)1024);
    else
        return asprintf("MEM : %.3f MB", (float)sizeInByte / (float)1048576);
}

void Log(LogLevel level, const string log, ...) {
    va_list ap;
    string time = GetCurrentTime();
    string usage = GetCurrentUsage();
    string content;

    va_start(ap, log);
    content = vasprintf(log, ap);
    va_end(ap);
    if (content == NULL)
        return;
    if (level == ERROR) {
        fprintf(stderr, COLOR_RED "[%s | %s] ERROR : %s" COLOR_RESET "\n", time, usage, content);
        exit(EXIT_FAILURE);
    }
    else if (level == SUCCESS)
        fprintf(stdout, COLOR_GRN "[%s | %s] SUCCESS : %s" COLOR_RESET "\n", time, usage, content);
    else if (level == WARNING)
        fprintf(stdout, COLOR_YEL "[%s | %s] WARNING : %s" COLOR_RESET "\n", time, usage, content);
    else if (level == INFORMATION)
        fprintf(stdout, "[%s | %s] INFORMATION : %s\n", time, usage, content);
    else
        fprintf(stdout, "[%s | %s] UNKNOWN LOG LEVEL : %s\n", time, usage, content);
    xfree(time, strlen(time));
    xfree(content, strlen(content));
    xfree(usage, strlen(usage));
}