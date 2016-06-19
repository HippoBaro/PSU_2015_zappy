//
// Created by barrauh on 6/18/16.
//

#include "Generic.h"
#include "Timer.h"

void    DestroyTimer(Timer *self) {
    xfree(self, sizeof(Timer));
}

static bool IsElapsed(Timer *self) {
    struct timeval current;
    uint64_t currMicro;

    if (gettimeofday(&current, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    currMicro = (uint64_t) (1000000 * current.tv_sec + current.tv_usec);
    Log(INFORMATION, "Target is %lu. Current is %lu. Delta is %lu.", self->target, currMicro, self->target - currMicro);
    if (currMicro > self->target)
        return true;
    return false;
}

Timer   *CreateAndStartTimer(suseconds_t target) {
    Timer *ret;
    struct timeval current;

    ret = xmalloc(sizeof(Timer));
    if (gettimeofday(&current, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    ret->target = (uint64_t) (1000000 * current.tv_sec + current.tv_usec + target);
    ret->isElapsed = &IsElapsed;
    return ret;
}