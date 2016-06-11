//
// Created by barrauh on 6/11/16.
//

#include "Generic.h"

void Log(LogLevel level, const string log) {
    if (level == ERROR) {
        fprintf(stderr, "ERROR : %s\n", log);
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