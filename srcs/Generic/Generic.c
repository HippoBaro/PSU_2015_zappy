//
// Created by barrauh on 6/11/16.
//

#include "Generic.h"

uint64_t on_heap = 0;

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
    if (ptr == NULL)
        return;
    on_heap -= size;
    free(ptr);
}

uint64_t GetTimeNowAsUSec() {
    struct timeval current;

    if (gettimeofday(&current, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    return (uint64_t) (1000000 * current.tv_sec + current.tv_usec);
}

int asymetricRandMinMax (int rolls, int min, int max) {
    int i = -1;
    int tmp, ret = max;
    while (++i < rolls) {
        tmp = randMinMax(min, max);
        ret = tmp < ret ? tmp : ret;
    }
    return ret;
}