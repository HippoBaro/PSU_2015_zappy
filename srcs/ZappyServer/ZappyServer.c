//
// Created by barrauh on 6/13/16.
//

#include "Drone.h"
#include "ZappyServer.h"

static ZappyServer *Configure(ZappyServer *self, Configuration *config) {
    if (self->status == SHUTDOWN)
        Log(WARNING, "Configuring a SHUTDOWN server will cause memory leaks. Free the server a recreate one.");
    srand((unsigned int) (config->seed != NULL ? *config->seed : time(NULL)));
    self->world = CreateMap(self, config->worldWidth, config->worldHeight);
    config->teamNames->forEachElements(config->teamNames, lambda(void, (void *team, void *dat), {
        self->teams->addElemFront(self->teams, CreateTeamFrom((string)team, config->initialClientPerTeam));
    }), NULL);
    self->configuration = config;
    self->status = CONFIGURED;
    Log(INFORMATION, "Server configured.");
    return self;
}

void DestroyZappyServer(ZappyServer *self) {
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

static Team *GetTeamFromTeamName(ZappyServer *self, string teamName) {
    t_list  *elem;

    if (self->teams == NULL || self->teams->countLinkedList(self->teams) == 0)
        return NULL;
    elem = FirstPred(self->teams, team, {
        return (bool) (strcmp(((Team *)team)->teamName, teamName) == 0);
    });
    if (elem == NULL || elem->data == NULL)
        return NULL;
    return elem->data;
}

ZappyServer *CreateZappyServer() {
    ZappyServer *ret;

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
    return ret;
}