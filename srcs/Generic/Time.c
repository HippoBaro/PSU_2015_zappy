//
// Created by barrauh on 6/27/16.
//

#include "Generic.h"

uint64_t		GetTimeNowAsUSec()
{
    struct timeval	current;

    if (gettimeofday(&current, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    return ((uint64_t)(1000000 * current.tv_sec + current.tv_usec));
}

struct timeval *GetTimeValFrom(uint64_t usec)
{
    struct timeval *ret;

    fprintf(stderr, "usec : %lu\n", usec);
    ret = xmalloc(sizeof(struct timeval));
    ret->tv_sec = usec / 1000000;
    ret->tv_usec = usec % 1000000;
    return (ret);
}