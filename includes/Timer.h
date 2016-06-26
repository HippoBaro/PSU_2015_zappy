/*
** Timer.h for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:38:24 2016 Etienne Pasteur
** Last update Mon Jun 27 00:38:59 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_TIMER_H
# define PSU_2015_ZAPPY_TIMER_H

# include <sys/time.h>
# include "Generic.h"

typedef struct	s_Timer {
    uint64_t	target;
    bool	(*isElapsed)(struct s_Timer *self);
}		Timer;

Timer		*CreateAndStartTimer(uint64_t target);
void		DestroyTimer(Timer *self);

#endif //PSU_2015_ZAPPY_TIMER_H
