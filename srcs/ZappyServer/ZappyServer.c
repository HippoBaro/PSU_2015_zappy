//
// Created by barrauh on 6/13/16.
//

#include <zconf.h>
#include <Drone.h>
#include <Team.h>
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

static void     NewClient(ZappyServer *server, Request *request) {
    Drone       *newDrone;
    Response    *response;

    newDrone = CreateDrone(NULL);
    newDrone->socketFd = request->socketFd;
    server->world->AddDrone(server->world->GetRandomTile(server->world), newDrone);
    response = CreateResponseFrom(request);
    response->message = strdup("BIENVENUE");
    response->Send(response);
    newDrone->status = WELCOME_SENT;
    request->Free(request);
}

static void ExecuteRequests(ZappyServer *server) {
    server->world->drones->forEachElements(server->world->drones, lambda(void, (void *drone, void *dat), {
        ((Drone *)drone)->ExecutePendingRequest(drone);
    }), NULL);
}

static Team *GetTeamFromTeamName(ZappyServer *self, string teamName) {
    t_list  *elem;

    if (self->teams == NULL || self->teams->countLinkedList(self->teams) == 0)
        return NULL;
    elem = self->teams->firstElementFromPredicate(self->teams, lambda(bool, (void *team, void *dat), {
        if (strcmp(((Team *)team)->teamName, teamName) == 0)
            return true;
        return false;
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        return NULL;
    return elem->data;
}

static void     InitDrone(ZappyServer *server, Drone *drone, Request *request) {
    Response    *response;
    Team        *team;

    team = server->GetTeamFromTeamName(server, request->message);
    if (team != NULL && team->CanAddNewDrone(team))
    {
        response = CreateResponseFrom(request);
        response->message = asprintf("%d", request->socketFd);
        response->Send(response);
        response = CreateResponseFrom(request);
        response->message = asprintf("%d %d", drone->mapTile->X, drone->mapTile->Y);
        response->Send(response);
        team->currentUsedSlot++;
        drone->team = team;
        drone->scheduledDeath = (uint64_t) (GetTimeNowAsUSec() + SecToUSec(10 * server->configuration->temporalDelay) * 126);
        drone->status = READY;
    }
    else
    {
        server->network->Disconnect(server->network, request->socketFd);
        drone->Die(drone, request);
    }
    request->Free(request);
}

static void     ExistingClient(ZappyServer *server, Request *request) {
    Drone       *drone;

    drone = server->GetAssociatedDrone(request, server->world);
    if (drone != NULL && drone->status == WELCOME_SENT)
        InitDrone(server, drone, request);
    else if (drone != NULL && drone->status == READY) {
        Log(INFORMATION, "New command from client %d : %s", drone->socketFd, request->message);
        request->Parse(request);
        if (request->requestedAction == UNKNOWN_ACTION)
            request->Free(request);
        else
            drone->CommitRequest(drone, request);
    }
    else
        request->Free(request);
}

static ZappyServer *StartInternal(ZappyServer *server) {
    Request *request;

    server->network = CreateNetwork(SERVER, (uint16_t) server->configuration->port, NULL);
    server->status = STARTED;
    Log(SUCCESS, "Zappy server started.");
    while (true) {
        if (feof(stdin))
            break;
        request = server->network->Receive(server->network, server->nextTimeout = server->GetNextRequestDelay(server));
        server->world->drones->forEachElements(server->world->drones, lambda(void, (void *drone, void *dat), {
            ((Drone *)drone)->UpdateLifeTime(drone);
        }), NULL);
        if (request != NULL)
        {
            request->Sanitize(request);
            if (request->type == NEW_CLIENT)
                NewClient(server, request);
            else
                ExistingClient(server, request);
        }
        ExecuteRequests(server);
    }
    return server->ShutDown(server);
}

static ZappyServer *Start(ZappyServer *server) {
    int i;

    i = 1;
    while (i <= 31) {
        if (i != SIGKILL && i != SIGSTOP)
            signal(i, lambda(void, (int sig), {
                Log(WARNING, "Received signal. Interrupting server. Signal was : %s (SIG = %d)", strsignal(sig), sig);
                server->ShutDown(server);
                server->Free(server);
                exit(EXIT_SUCCESS);
            }));
        ++i;
    }
    return StartInternal(server);
}

static Drone    *GetAssociatedDrone(Request *request, Map *map) {
    t_list *elem;

    elem = map->drones->firstElementFromPredicate(map->drones, lambda(bool, (void *drone, void *data), {
        if (((Drone *)drone)->socketFd == request->socketFd)
            return true;
        return false;
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        return NULL;
    return elem->data;
}

static struct timeval *GetNextRequestDelay(ZappyServer *server) {
    uint64_t next;
    uint64_t droneT;
    struct timeval nextTimeval;
    struct timeval current;
    struct timeval *ret;

    next = UINT64_MAX;
    if (server->nextTimeout != NULL)
        xfree(server->nextTimeout, sizeof(struct timeval));
    server->world->drones->forEachElements(server->world->drones, lambda(void, (void *drone, void *data), {
        if (((Drone *)drone)->currentPendingRequest != NULL && ((Drone *)drone)->currentPendingRequest->timer->target < next)
            next = ((Drone *)drone)->currentPendingRequest->timer->target;
        if (((Drone *)drone)->status == READY) {
            droneT = ((Drone *) drone)->scheduledDeath;
            if (droneT > 0 && droneT < next)
                next = droneT;
        }
    }), NULL);
    if (next == UINT64_MAX)
        return NULL;
    ret = xmalloc(sizeof(struct timeval));
    nextTimeval.tv_sec = next / 1000000;
    nextTimeval.tv_usec = next % 1000000;
    gettimeofday(&current, NULL);
    timersub(&nextTimeval, &current, ret);
    return ret;
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
    ret->Start = &Start;
    ret->GetAssociatedDrone = &GetAssociatedDrone;
    ret->GetNextRequestDelay = &GetNextRequestDelay;
    ret->GetTeamFromTeamName = &GetTeamFromTeamName;
    ret->ShutDown = lambda(ZappyServer *, (ZappyServer *server), {
        if (server->status != STARTED)
            Log(WARNING, "Trying to shutdown an non-started server !");
        Log(WARNING, "Shutting down Zappy Server");
        server->status = SHUTDOWN;
        return server;
    });
    ret->Free = &DestroyZappyServer;
    Log(INFORMATION, "Server created.");
    return ret;
}