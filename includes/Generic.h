//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_GENERIC_H
#define PSU_2015_ZAPPY_GENERIC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <limits.h>
#include <signal.h>

#define lambda(ret, args, body) ({ ret l_anonymous_functions_name args body &l_anonymous_functions_name; })
#define atomicdup(type, value) lambda(type *, (void), {type *tmp = xmalloc(sizeof(type));*tmp=value;return tmp;})()
#define randMinMax(low, high) (rand() % (high - low + 1) + low)

#define COLOR_RED   "\x1B[31m"
#define COLOR_GRN   "\x1B[32m"
#define COLOR_YEL   "\x1B[33m"
#define COLOR_BLU   "\x1B[34m"
#define COLOR_MAG   "\x1B[35m"
#define COLOR_CYN   "\x1B[36m"
#define COLOR_WHT   "\x1B[37m"
#define COLOR_RESET "\x1B[0m"

typedef char * string;

typedef enum e_bool {
    false = 0,
    true = 1
}           bool;

typedef enum e_LogLevel {
    INFORMATION,
    SUCCESS,
    WARNING,
    ERROR
}           LogLevel;

typedef enum e_RequestType {
    UNKNOWN_REQUESTTYPE = 0,
    NEW_CLIENT = 1,
    EXISTING_CLIENT = 0
}               RequestType;

typedef enum e_Destination {
    EVERYBODY,
    SUBSET
}           Destination;

typedef enum e_ZappyServerStatus {
    UNINITIALIZED,
    CONFIGURED,
    STARTED,
    SHUTDOWN
}           ZappyServerStatus;

typedef enum e_Action {
    UNKNOWN_ACTION = -1,
    TAKE = 0,
    DROP = 1,
    FORK = 2,
    DIE = 3,
    MOVE = 4,
    ROTATE = 5,
    LOOK_INVENTORY = 6,
    EXPULSE = 7,
    BROADCAST = 8,
    INCANT = 9,
    ASK_SLOT = 10,
    LOOK = 11
}               Action;

typedef enum e_Selection {
    FIRST,
    SECOND,
    BOTH
}           Selection;

typedef enum e_ItemType {
    UNKNOWN_ITEMTYPE = -1,
    LINEMATE = 0,
    DERAUMERE = 1,
    SIBUR = 2,
    MENDIANE = 3,
    PHIRAS = 4,
    THYSTAME = 5,
    NOURRITURE = 6
}           ItemType;

typedef enum e_Rotation {
    TOP = 0,
    RIGHT = 90,
    BOTTOM = 180,
    LEFT = 270
}               Rotation;

void Log(LogLevel level, const string log, ...);
void *xmalloc(size_t size);
void xfree(void *ptr, size_t size);
string strappend(string dest, string source, Selection freeOption);
int asymetricRandMinMax (int rolls, int min, int max);
string asprintf(const char *fmt, ...);

#endif //PSU_2015_ZAPPY_GENERIC_H
