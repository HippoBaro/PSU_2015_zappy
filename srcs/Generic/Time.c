/*
** Time.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Generic
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 01:31:35 2016 Etienne Pasteur
** Last update Mon Jun 27 01:32:02 2016 Etienne Pasteur
*/

#include "Generic.h"

uint64_t		GetTimeNowAsUSec()
{
    struct timeval	current;

    if (gettimeofday(&current, NULL) != 0)
        Log(ERROR, "Unable to start Timer -- error getting current time.");
    return ((uint64_t)(1000000 * current.tv_sec + current.tv_usec));
}

struct timeval		*GetTimeValFrom(uint64_t usec)
{
    struct timeval	*ret;

    fprintf(stderr, "usec : %lu\n", usec);
    ret = xmalloc(sizeof(struct timeval));
    ret->tv_sec = usec / 1000000;
    ret->tv_usec = usec % 1000000;
    return (ret);
}
