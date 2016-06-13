//
// Created by barrauh on 6/11/16.
//

#include <ctype.h>
#include "Generic.h"

void Log(LogLevel level, const string log) {
    if (level == ERROR) {
        fprintf(stderr, "ERROR : %s\n", log);
        exit(EXIT_FAILURE);
    }
    else if (level == WARNING) {
        fprintf(stdout, "WARNING : %s\n", log);
    }
    else if (level == INFORMATION) {
        fprintf(stdout, "INFORMATION : %s\n", log);
    }
    else {
        fprintf(stdout, "UNKNOWN LOG LEVEL : %s\n", log);
    }
}

void *xmalloc(size_t size) {
    void    *ret;

    if ((ret = malloc(size)) == NULL) {
        Log(ERROR, (string const) "Failed to allocate memory. Abording.");
        exit(EXIT_FAILURE);
    }
    return ret;
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
        free(dest);
    if ((freeOption == SECOND || freeOption == BOTH)  && source != NULL)
        free(source);
    return new_str;
}

string tolowers(string str)
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