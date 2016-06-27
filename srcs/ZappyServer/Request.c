/*
** Request.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/ZappyServer
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 02:22:28 2016 Etienne Pasteur
** Last update Mon Jun 27 02:22:28 2016 Etienne Pasteur
*/

#include "Drone.h"
#include "ZappyServer.h"

static uint64_t		GetNextRequestDelayAsUSec(ZappyServer *server)
{
  uint64_t		next;
  uint64_t		droneT;

  next = UINT64_MAX;
  if (server->nextTimeout != NULL)
    xfree(server->nextTimeout, sizeof(struct timeval));
  ForEach(server->world->drones, drone, {
      if (((Drone *)drone)->currentPendingRequest != NULL
	  && ((Drone *)drone)->currentPendingRequest->timer->target < next)
	next = ((Drone *)drone)->currentPendingRequest->timer->target;
      if (((Drone *)drone)->status == READY) {
	droneT = ((Drone *) drone)->scheduledDeath;
	if (droneT > 0 && droneT < next)
	  next = droneT;
      }
    });
  return (next);
}

static struct timeval	*GetNextRequestDelay(ZappyServer *server)
{
  struct timeval	nextTimeval;
  struct timeval	current;
  struct timeval	*ret;
  uint64_t		next;

  next = GetNextRequestDelayAsUSec(server);
  if (next == UINT64_MAX)
    return (NULL);
  next += 100;
  ret = xmalloc(sizeof(struct timeval));
  nextTimeval.tv_sec = next / 1000000;
  nextTimeval.tv_usec = next % 1000000;
  gettimeofday(&current, NULL);
  timersub(&nextTimeval, &current, ret);
  return (ret);
}

static void		ExecuteRequests(ZappyServer *server)
{
  ForEach(server->world->drones, drone, {
      ((Drone *)drone)->ExecutePendingRequest(drone);
    });
}

void			InitZappyServerRequest(ZappyServer *server)
{
  server->ExecuteRequests = &ExecuteRequests;
  server->GetNextRequestDelay = &GetNextRequestDelay;
}
