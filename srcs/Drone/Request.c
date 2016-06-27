/*
** Request.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:28:04 2016 Etienne Pasteur
** Last update Sun Jun 26 18:50:30 2016 Etienne Pasteur
*/

#include "ZappyServer.h"
#include "Drone.h"

static void	ValidateAndStartRequestTimer(Drone *d, Request *r)
{
  Response	*response;

  if ((response = r->Validate(r, d)) != NULL)
    {
      response->Send(response);
      d->currentPendingRequest->Free(d->currentPendingRequest);
      d->currentPendingRequest = NULL;
      d->ExecutePendingRequest(d);
      return;
    }
  d->currentPendingRequest->RequestDidBecomeActive(
						   d->currentPendingRequest, d);
  d->currentPendingRequest->timer = CreateAndStartTimer(
							r->GetCompletionTime(r, d->mapTile->map->server));
}

static Drone	*CommitRequest(Drone *drone, Request *request)
{
  if (request != NULL && request->requestedAction == DIE)
    drone->Die(drone, request);
  else if (drone->currentPendingRequest != NULL &&
	   drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
    drone->pendingRequests->addElemFront(drone->pendingRequests, request);
  else if (drone->currentPendingRequest == NULL)
    {
      drone->currentPendingRequest = request;
      ValidateAndStartRequestTimer(drone, drone->currentPendingRequest);
    }
  return (drone);
}

static Drone	*ExecutePendingRequest(Drone *drone)
{
  t_list	*elem;

  if (drone->currentPendingRequest == NULL &&
      drone->pendingRequests->countLinkedList(drone->pendingRequests) == 0)
    return (drone);
  else if (drone->currentPendingRequest == NULL &&
	   drone->pendingRequests->countLinkedList(drone->pendingRequests) > 0) {
    elem = drone->pendingRequests->getElementFirst(drone->pendingRequests);
    drone->currentPendingRequest = elem->data;
    drone->pendingRequests->removeThisElem(drone->pendingRequests, elem);
    ValidateAndStartRequestTimer(drone, drone->currentPendingRequest);
  }
  if (drone->currentPendingRequest != NULL)
    drone->ExecuteCurrentPendingRequest(drone);
  return (drone);
}

static bool	UpdateLifeTime(Drone *drone)
{
  uint64_t	now;
  t_list	*tList;
  Item	*food;

  now = GetTimeNowAsUSec();
  if (drone->scheduledDeath == 0)
    return (false);
  if (now >= drone->scheduledDeath) {
    tList = FirstPred(drone->inventory, elem, {
	return (bool)(((Item *)elem)->type == NOURRITURE);
      });
    if (tList != NULL && (food = tList->data) != NULL) {
      drone->scheduledDeath =
	(uint64_t) (now + food->quantity +
		    SecToUSec(food->quantity /
			      drone->mapTile->map->server->configuration->temporalDelay) *
		    126);
      drone->DropInternal(drone, NOURRITURE, food->quantity, true);
    }
    else
      drone->Die(drone, NULL);
    return (true);
  }
  return (false);
}

void	InitDroneRequest(Drone *selfDrone)
{
  selfDrone->UpdateLifeTime = &UpdateLifeTime;
  selfDrone->CommitRequest = &CommitRequest;
  selfDrone->ExecutePendingRequest = &ExecutePendingRequest;
  selfDrone->ExecuteCurrentPendingRequest = lambda(void, (Drone *drone), {
      Response *response;

      if (drone->currentPendingRequest->timer->isElapsed(
							 drone->currentPendingRequest->timer))
	{
	  response = drone->currentPendingRequest->Execute(
							   drone->currentPendingRequest, drone);
	  if (response != NULL)
	    response->Send(response);
	  drone->currentPendingRequest->Free(drone->currentPendingRequest);
	  drone->currentPendingRequest = NULL;
	  drone->ExecutePendingRequest(drone);
	}
    });
}
