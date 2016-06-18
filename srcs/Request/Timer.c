//
// Created by barrauh on 6/18/16.
//

#include "Generic.h"
#include "Timer.h"

void    DestroyTimer(Timer *self) {
    xfree(self->start, sizeof(struct timeval));
    xfree(self, sizeof(Timer));
}

Timer   *CreateAndStartTimer(suseconds_t target) {
    Timer *ret;

    ret = xmalloc(sizeof(Timer));
    ret->start = xmalloc(sizeof(struct timeval));
    if (gettimeofday(ret->start, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    ret->timer = target;
    ret->isElapsed = lambda(bool, (Timer *self), {
        struct timeval *current = xmalloc(sizeof(struct timeval));

        if (gettimeofday(current, NULL) != 0)
            Log(ERROR, "Unable to start Timer -- error getting current time.");
        if (current->tv_usec > (self->start->tv_usec + self->timer))
            return true;
        return false;
    });
    return ret;
}