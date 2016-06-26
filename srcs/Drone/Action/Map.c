/*
** Map.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 14:03:04 2016 Etienne Pasteur
** Last update Sun Jun 26 14:53:29 2016 Etienne Pasteur
*/

#include "ZappyServer.h"
#include "Drone.h"

void			func_expulse(void * droneD, void *dat)
{
  Drone			*self;
  Drone			*drone;
  Response		*res;

  self = (Drone*)dat;
  if ((drone = droneD) == self)
    return;
  drone->mapTile->RemoveDrone(drone->mapTile, drone);
  drone->mapTile = self->mapTile->GetTopTile(self, drone->mapTile->map);
  drone->mapTile->AddDrone(drone->mapTile, drone);
  res = CreateResponseFromFdWithMessage(drone->socketFd,
					asprintf("deplacement: %d",
						 self->mapTile->map->GetTileNumberForDrone(
											   self->mapTile,
											   drone, self->mapTile->map)));
  res->Send(res);
}

Response		*Look(Drone *self, Request *request)
{
  return (CreateResponseFromFdWithMessage(self->socketFd,
					  self->GetDroneSight(self, self->mapTile->map)));
}

Response		*Expulse(Drone *self, Request *request)
{
    self->mapTile->drones->forEachElements(self->mapTile->drones,
					 &func_expulse, self);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

Response		*Die(Drone *s, Request *request)
{
  LinkedList(Drones)	*drs;
  t_list		*elem;
  t_list		*elem2;

  if (s->team != NULL)
    s->team->currentUsedSlot--;
  Send(CreateResponseFromFdWithMessage(s->socketFd, strdup("mort")));
  s->mapTile->map->server->network->Disconnect(s->mapTile->map->server->network,
					       s->socketFd);
  drs = s->mapTile->map->drones;
  elem = FirstPred(drs, drone, {
				       return ((bool)(s->socketFd == ((Drone *)drone)->socketFd));
				     });
  drs->removeThisElem(drs, elem);
  drs = s->mapTile->drones;
  elem2 = FirstPred(drs, drone, {
				       return ((bool)(s->socketFd == ((Drone *)drone)->socketFd));
				     });
  drs->freeThisElem(drs, (void (*)(void *)) &DestroyDrone, elem2);
  Log(INFORMATION, "Drone is dead.");
  return (NULL);
}
