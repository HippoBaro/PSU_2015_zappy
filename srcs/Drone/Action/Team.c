/*
** Team.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:06:29 2016 Etienne Pasteur
** Last update Sun Jun 26 15:45:53 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*GetTeamSlot(struct s_Drone *self, Request *request)
{
  return (CreateResponseFromFdWithMessage(
					  self->socketFd,
					  asprintf("%d",self->team->maxSlot - self->team->currentUsedSlot)));
}

Response	*Broadcast(Drone *self, Request *request)
{
  Drone		*target;
  MapTile	*tile;
  Response	*response;
  int		tileNumber;

  tile = NULL;
  self->mapTile->map->drones->forEachElements(self->mapTile->map->drones,lambda(void, (void *drone, void *dat), {
    target = drone;
    if (drone == self)
      return;
    tile = target->mapTile->map->GetTileReceivingSound(self, target, self->mapTile->map);
    if (tile == NULL)
      Log(ERROR, "GetTileReceivingSound returned NULL. This should not append.");
    Log(INFORMATION, "Receiving tile coords are : %d,%d", tile->X, tile->Y);
    tileNumber = target->mapTile->map->GetTileNumberForDrone(tile, target, target->mapTile->map);
    if (tileNumber < 0)
      Log(ERROR, "GetTileNumberForDrone returned < 0. This should not append.");
    response = CreateResponseFromFdWithMessage(target->socketFd, asprintf("message %d,%s", tileNumber, request->actionSubject));
    response->Send(response);
      }), NULL);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}
