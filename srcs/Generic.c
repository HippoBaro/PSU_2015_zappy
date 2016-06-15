//
// Created by barrauh on 6/11/16.
//

#include "Generic.h"

static unsigned long on_heap = 0;
void *xmalloc(size_t size) {
    void    *ret;

    if ((ret = malloc(size)) == NULL) {
        Log(ERROR, (string const) "Failed to allocate memory. Abording.");
        exit(EXIT_FAILURE);
    }
    on_heap += size;
    return ret;
}

void *xcalloc(size_t nelem, size_t elsize)
{
    void *ret;

    ret = xmalloc (nelem * elsize);
    bzero (ret, nelem * elsize);
    return (ret);
}

void xfree(void *ptr, size_t size) {
    on_heap -= size;
    free(ptr);
}
static string vasprintf(const char *fmt, va_list ap)
{
    va_list apcpy;
    size_t size;
    char *ret;

    va_copy(apcpy, ap);
    size = (size_t) (vsnprintf(NULL, 0, fmt, apcpy) + 1);
    va_end(apcpy);
    ret = xcalloc(1, size);
    if (vsnprintf(ret, size, fmt, ap) == -1)
        return NULL;
    return ret;
}

static string asprintf(const char *fmt, ...)
{
    string ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vasprintf(fmt, ap);
    va_end(ap);
    return ret;
}

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
        fprintf(stderr, COLOR_RED "[%s | %s] ERROR : %s\n" COLOR_RESET, time, usage, content);
        exit(EXIT_FAILURE);
    }
    else if (level == SUCCESS)
        fprintf(stdout, COLOR_GRN "[%s | %s] SUCCESS : %s\n" COLOR_RESET, time, usage, content);
    else if (level == WARNING)
        fprintf(stdout, COLOR_YEL "[%s | %s] WARNING : %s\n" COLOR_RESET, time, usage, content);
    else if (level == INFORMATION)
        fprintf(stdout, "[%s | %s] INFORMATION : %s\n", time, usage, content);
    else
        fprintf(stdout, "[%s | %s] UNKNOWN LOG LEVEL : %s\n", time, usage, content);
    xfree(time, strlen(time));
    xfree(content, strlen(content));
    xfree(usage, strlen(usage));
}

string strappend(string dest, string source, Selection freeOption) {
    char *new_str;
    if (dest == NULL)
        new_str = xmalloc(strlen(source) + 1);
    else
        new_str = xmalloc(strlen(dest) + strlen(source) + 1);
    new_str[0] = '\0';
    if (dest != NULL)
        strcat(new_str, dest);
    strcat(new_str, source);
    if ((freeOption == FIRST || freeOption == BOTH)  && dest != NULL)
        xfree(dest, strlen(dest));
    if ((freeOption == SECOND || freeOption == BOTH)  && source != NULL)
        xfree(source, strlen(source));
    return new_str;
}

string strtolower(string str)
{
    int i;

    i = 0;
    while(str[i])
    {
        putchar(tolower(str[i]));
        i++;
    }
    return(str);
}