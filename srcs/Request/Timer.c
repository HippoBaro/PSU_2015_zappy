/*
** Timer.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Request
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:09:54 2016 Etienne Pasteur
** Last update Sun Jun 26 17:11:49 2016 Etienne Pasteur
*/

#include "Generic.h"
#include "Timer.h"

void			DestroyTimer(Timer *self)
{
  xfree(self, sizeof(Timer));
}

static bool		IsElapsed(Timer *self)
{
  struct timeval	current;
  uint64_t		currMicro;

  if (gettimeofday(&current, NULL) != 0)
    Log(ERROR, "Unable to start Timer -- error getting current time.");
  currMicro = (uint64_t) (1000000 * current.tv_sec + current.tv_usec);
  if (currMicro > self->target)
    return (true);
  return (false);
}

Timer			*CreateAndStartTimer(uint64_t target)
{
  Timer			*r;
  struct timeval	current;

  r = xmalloc(sizeof(Timer));
  if (gettimeofday(&current, NULL) != 0)
    Log(ERROR, "Unable to start Timer -- error getting current time.");
  r->target = (uint64_t) (1000000 * current.tv_sec + current.tv_usec + target);
  r->isElapsed = &IsElapsed;
  return (r);
}
