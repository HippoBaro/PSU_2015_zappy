/*
** Drone.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:27:01 2016 Etienne Pasteur
** Last update Mon Jun 27 01:40:25 2016 Etienne Pasteur
*/

#include "ZappyServer.h"
#include "Drone.h"

void	DestroyDrone(Drone *drone)
{
  drone->inventory->freeAll(drone->inventory,
			    (void (*)(void *)) &DestroyItem);
  drone->inventory->Free(drone->inventory);
  drone->pendingRequests->freeAll(
				  drone->pendingRequests,
				  (void (*)(void *)) &DestroyRequest);
  drone->pendingRequests->Free(drone->pendingRequests);
  xfree(drone, sizeof(Drone));
}

Drone	*CreateDrone(Team *team)
{
  Drone	*ret;

  ret = xmalloc(sizeof(Drone));
  ret->pendingRequests = CreateLinkedList();
  ret->inventory = CreateLinkedList();
  ret->mapTile = NULL;
  ret->team = team;
  ret->currentPendingRequest = NULL;
  ret->level = 1;
  ret->status = NEW;
  ret->scheduledDeath = (uint64_t) 0;
  ret->rotation = TOP;
  ret->DuplicateDrone = &DuplicateDrone;
  ret->Die = &Die;
  ret->DropInternal = &DropInternal;
  ret->GetDroneSight = &GetDroneSight;
  ret->Free = &DestroyDrone;
  InitDroneMove(ret);
  InitDroneRequest(ret);
  return (ret);
}
