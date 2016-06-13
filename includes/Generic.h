//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_GENERIC_H
#define PSU_2015_ZAPPY_GENERIC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define lambda(ret, args, body) ({ ret l_anonymous_functions_name args body &l_anonymous_functions_name; })

typedef char * string;

typedef enum e_bool {
    false,
    true
}           bool;

typedef enum e_LogLevel {
    INFORMATION,
    WARNING,
    ERROR
}           LogLevel;

typedef enum e_Destination {
    EVERYBODY,
    SUBSET
}           Destination;

typedef enum e_Action {
    UNKNOWN = -1,
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
    LINEMATE = 0,
    DERAUMERE = 1,
    SIBUR = 2,
    MENDIANE = 3,
    PHIRAS = 4,
    THYSTAME = 5
    //todo Food ? Can't find it in subject.
}           ItemType;

typedef enum e_Rotation {
    LEFT = 0,
    RIGHT = 1
}               Rotation;

void Log(LogLevel level, const string log);
void *xmalloc(size_t size);
string strappend(string dest, string source, Selection freeOption);

#endif //PSU_2015_ZAPPY_GENERIC_H
