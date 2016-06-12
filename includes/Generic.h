//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_GENERIC_H
#define PSU_2015_ZAPPY_GENERIC_H

#include <stdio.h>
#include <stdlib.h>

#define lambda(l_ret_type, l_arguments, l_body)         \
  ({                                                    \
   l_ret_type l_anonymous_functions_name l_arguments   \
   l_body                                            \
   &l_anonymous_functions_name;                        \
   })

typedef char * string;

typedef enum e_bool {
    false,
    true
}           bool;

typedef enum e_LogLevel {
    INFORMATION,
    WARNING,
    ERROR
}       LogLevel;

typedef enum e_Destination {
    EVERYBODY,
    SUBSET
}       Destination;

typedef enum e_Action {
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

typedef enum e_Rotation {
    LEFT = 0,
    RIGHT = 1
}               Rotation;

void Log(LogLevel level, const string log);
void *xmalloc(size_t size);

#endif //PSU_2015_ZAPPY_GENERIC_H
