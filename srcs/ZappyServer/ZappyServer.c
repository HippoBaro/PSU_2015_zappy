/*
** ZappyServer.c for in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/ZappyServer
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 02:22:48 2016 Etienne Pasteur
** Last update Mon Jun 27 02:23:58 2016 Etienne Pasteur
*/

#include "Drone.h"
#include "ZappyServer.h"

static ZappyServer	*Configure(ZappyServer *self, Configuration *config)
{
  srand((unsigned int) (config->seed != NULL ? *config->seed : time(NULL)));
  self->world = CreateMap(self, config->worldWidth, config->worldHeight);
  ForEach(config->teamNames, team, {
      Team *teamD;

      teamD = CreateTeamFrom((string)team, config->initialClientPerTeam);
      self->teams->addElemFront(self->teams, teamD);
    });
  self->configuration = config;
  self->status = CONFIGURED;
  Log(INFORMATION, "Server configured.");
  return (self);
}

void			DestroyZappyServer(ZappyServer *self)
{
  self->teams->freeAll(self->teams, (void (*)(void *)) &DestroyTeam);
  self->teams->Free(self->teams);
  self->world->Free(self->world);
  self->configuration->Free(self->configuration);
  if (self->nextTimeout != NULL)
    xfree(self->nextTimeout, sizeof(struct timeval));
  self->network->DeleteNetwork(self->network);
  xfree(self, sizeof(ZappyServer));
  Log(INFORMATION, "Server was successfully destroyed.");
}

static Team		*GetTeamFromTeamName(ZappyServer *self, string teamName)
{
  t_list		*elem;

  if (self->teams == NULL || self->teams->countLinkedList(self->teams) == 0)
    return NULL;
  elem = FirstPred(self->teams, team, {
      return (bool) (strcmp(((Team *)team)->teamName, teamName) == 0);
    });
  if (elem == NULL || elem->data == NULL)
    return NULL;
  return elem->data;
}

ZappyServer		*CreateZappyServer()
{
  ZappyServer		*ret;

  ret = xmalloc(sizeof(ZappyServer));
  ret->status = UNINITIALIZED;
  ret->nextTimeout = NULL;
  ret->configuration = CreateConfiguration();
  ret->world = NULL;
  ret->teams = CreateLinkedList();
  ret->Configure = &Configure;
  ret->GetTeamFromTeamName = &GetTeamFromTeamName;
  ret->ShutDown = lambda(ZappyServer *, (ZappyServer *server), {
      Log(WARNING, "Shutting down Zappy Server");
      server->status = SHUTDOWN;
      return server;
    });
  ret->Free = &DestroyZappyServer;
  InitZappyServerRequest(ret);
  InitZappyServerDrone(ret);
  InitZappyServerLifeCycle(ret);
  Log(INFORMATION, "Server created.");
  return (ret);
}
