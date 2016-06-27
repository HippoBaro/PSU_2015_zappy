/*
** LifeCycle.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/ZappyServer
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 02:17:38 2016 Etienne Pasteur
** Last update Mon Jun 27 02:20:42 2016 Etienne Pasteur
*/

#include "Drone.h"
#include "ZappyServer.h"

static ZappyServer	*UpdateState(ZappyServer *self)
{
  ForEach(self->world->drones, drone, {
      ((Drone *)drone)->UpdateLifeTime(drone);
    });
  ForEach(self->teams, team, {
      ((Team *)team)->UpdateTeam(team);
    });
  return (self);
}

static ZappyServer	*StartInternal(ZappyServer *server)
{
  Request		*request;

  server->network = CreateNetwork(SERVER, (uint16_t)
				  server->configuration->port, NULL);
  server->status = STARTED;
  Log(SUCCESS, "Zappy server started.");
  while (true) {
    if (feof(stdin))
      break;
    request = server->network->Receive(server->network, server->nextTimeout
				       = server->GetNextRequestDelay(server));
    server->UpdateState(server);
    if (request != NULL)
      {
	request->Sanitize(request);
	if (request->type == NEW_CLIENT)
	  server->NewClient(server, request);
	else
	  server->ExistingClient(server, request);
      }
    server->ExecuteRequests(server);
  }
  return (server->ShutDown(server));
}

static ZappyServer	*Start(ZappyServer *server)
{
  int			i;

  i = 1;
  while (i <= 31) {
    if (i != SIGKILL && i != SIGSTOP)
      signal(i, lambda(void, (int sig), {
	    Log(WARNING, "Received signal. Interrupting server. "
		"Signal was : %s (SIG = %d)", strsignal(sig), sig);
	    server->ShutDown(server);
	    server->Free(server);
	    exit(EXIT_SUCCESS);
	  }));
    ++i;
  }
  return (StartInternal(server));
}

void			InitZappyServerLifeCycle(ZappyServer *server)
{
  server->Start = &Start;
  server->UpdateState = &UpdateState;
}
