/*
** Team.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:06:29 2016 Etienne Pasteur
** Last update Sun Jun 26 15:45:53 2016 Etienne Pasteur
*/

#include <ZappyServer.h>
#include "Drone.h"

Response	*GetTeamSlot(struct s_Drone *self, Request *request)
{
  string responseString;

  responseString = asprintf("%d", self->team->maxSlot
                                  - self->team->currentUsedSlot);
  return (CreateResponseFromFdWithMessage(self->socketFd, responseString);
}

Response	*Broadcast(Drone *self, Request *request)
{
  Drone		*target;
  MapTile	*tile;
  Response	*response;
  int		tileNumber;
  string    resStr;

  tile = NULL;
  ForEach(self->mapTile->map->drones, drone, {
    target = drone;
    if (drone == self)
      return;
    tile = target->mapTile->map->
            GetTileReceivingSound(self, target, self->mapTile->map);
    Log(INFORMATION, "Receiving tile coords are : %d,%d", tile->X, tile->Y);
    tileNumber = target->mapTile->map->
            GetTileNumberForDrone(tile, target, target->mapTile->map);
    resStr = asprintf("message %d,%s", tileNumber, request->actionSubject);
    response = CreateResponseFromFdWithMessage(target->socketFd, resStr);
    response->Send(response);
      });
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

Response		*Fork(Drone *self, Request *request)
{
  self->team->ScheduleAddSlot(self->team, self->mapTile->map->server->
          configuration->temporalDelay);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}
