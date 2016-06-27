/*
** Team.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Team
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:18:43 2016 Etienne Pasteur
** Last update Mon Jun 27 02:15:10 2016 Etienne Pasteur
*/

#include "Team.h"

void		DestroyTeam(Team *self)
{
  if (self->teamName != NULL)
    xfree(self->teamName, strlen(self->teamName));
  self->nextslots->freeAll(self->nextslots, lambda(void, (void *dat), {
	xfree(dat, sizeof(uint64_t));
      }));
  self->nextslots->Free(self->nextslots);
  xfree(self, sizeof(Team));
}

static Team	*UpdateTeam(Team *self)
{
  uint64_t	timeNow;
  t_list	*elem;

  timeNow = GetTimeNowAsUSec();
  while (true)
    {
      elem = FirstPred(self->nextslots, next, {
	  return (timeNow >= *((uint64_t *)next));
	});
      if (elem == NULL)
	break;
      self->maxSlot++;
      self->nextslots->freeThisElem(self->nextslots, lambda(void, (void *elm), {
	    xfree(elm, sizeof(uint64_t));
	  }), elem);
    }
  return (self);
}

static bool	CanAddNewDrone(Team *self)
{
  if (self->currentUsedSlot < self->maxSlot)
    return (true);
  return (false);
}

static Team	*ScheduleAddSlot(Team *self, double temporalDelay)
{
  uint64_t	next;

  next = (uint64_t) (GetTimeNowAsUSec() + SecToUSec(300 / temporalDelay));
  self->nextslots->addElemFront(self->nextslots, atomicdup(uint64_t, next));
  return (self);
}

Team		*CreateTeamFrom(string name, int maxSlot)
{
  Team		*ret;

  ret = xmalloc(sizeof(Team));
  ret->teamName = strdup(name);
  ret->currentUsedSlot = 0;
  ret->maxSlot = maxSlot;
  ret->nextslots = CreateLinkedList();
  ret->CanAddNewDrone = &CanAddNewDrone;
  ret->GetAvailableSlots = lambda(int, (Team *self), {
      return (self->maxSlot - self->currentUsedSlot);
    });
  ret->ScheduleAddSlot = &ScheduleAddSlot;
  ret->UpdateTeam = &UpdateTeam;
  ret->Free = &DestroyTeam;
  return (ret);
}
