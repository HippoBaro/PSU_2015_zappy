/*
** Team.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Team
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:18:43 2016 Etienne Pasteur
** Last update Sun Jun 26 17:19:39 2016 Etienne Pasteur
*/

#include "Team.h"

void            DestroyTeam(Team *self)
{
  if (self->teamName != NULL)
    xfree(self->teamName, strlen(self->teamName));
  xfree(self, sizeof(Team));
}

static int      GetAvailableSlots(Team *self)
{
  return (self->maxSlot - self->currentUsedSlot);
}

static bool     CanAddNewDrone(Team *self)
{
  if (self->currentUsedSlot < self->maxSlot)
    return (true);
  return (false);
}

Team            *CreateTeamFrom(string name, int maxSlot)
{
  Team    *ret;

  ret = xmalloc(sizeof(Team));
  ret->teamName = strdup(name);
  ret->currentUsedSlot = 0;
  ret->maxSlot = maxSlot;
  ret->CanAddNewDrone = &CanAddNewDrone;
  ret->GetAvailableSlots = &GetAvailableSlots;
  ret->Free = &DestroyTeam;
  return (ret);
}
