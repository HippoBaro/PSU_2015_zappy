//
// Created by barrauh on 6/18/16.
//

#include <sys/time.h>
#include "Generic.h"

#ifndef PSU_2015_ZAPPY_TIMER_H
#define PSU_2015_ZAPPY_TIMER_H

typedef struct              s_Timer {
    uint64_t                target;
    bool                    (*isElapsed)(struct s_Timer *self);
}                           Timer;

Timer   *CreateAndStartTimer(suseconds_t target);
void    DestroyTimer(Timer *self);

#endif //PSU_2015_ZAPPY_TIMER_H
