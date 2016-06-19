//
// Created by barrauh on 6/13/16.
//

#include <zconf.h>
#include <Drone.h>
#include "ZappyServer.h"

static ZappyServer *Configure(ZappyServer *self, Configuration *config) {
    int i;

    if (self->status == SHUTDOWN)
        Log(WARNING, "Configuring a SHUTDOWN server will cause memory leaks. Free the server a recreate one.");
    i = 1;
    while (i <= 31) {
        if (i != SIGKILL && i != SIGSTOP)
            signal(i, lambda(void, (int sig), {
                Log(WARNING, "Received signal. Interrupting server. Signal was : %s (SIG = %d)", strsignal(sig), sig);
                self->ShutDown(self);
                self->Free(self);
                exit(EXIT_SUCCESS);
            }));
        ++i;
    }
    srand((unsigned int) (config->seed != NULL ? *config->seed : time(NULL)));
    self->world = CreateMap(config->worldWidth, config->worldHeight);
    self->temporalDelay = config->temporalDelay;
    self->temporalDelay = config->temporalDelay;
    //todo create teams
    self->configuration = config;
    self->status = CONFIGURED;
    Log(INFORMATION, "Server configured.");
    return self;
}

void DestroyZappyServer(ZappyServer *self) {
    self->teams->freeAll(self->teams, NULL); //todo set team destructor
    self->teams->Free(self->teams);
    self->world->Free(self->world);
    self->configuration->Free(self->configuration);
    xfree(self, sizeof(ZappyServer));
    Log(INFORMATION, "Server was successfully destroyed.");
}

static void     NewClient(ZappyServer *server, Request *request) {
    Drone       *newDrone;
    Response    *response;

    //todo verify if slot exist
    newDrone = CreateDrone();
    newDrone->socketFd = request->socketFd;
    server->world->AddDrone(server->world->GetRandomTile(server->world), newDrone);
    response = CreateResponseFrom(request);
    response->message = strdup("BIENVENUE");
    response->Send(response);
    newDrone->status = WELCOME_SENT;
}

static void     ExistingClient(ZappyServer *server, Request *request) {
    Drone       *drone;
    Response    *response;

    drone = server->GetAssociatedDrone(request, server->world);
    if (drone->status == WELCOME_SENT) {
        response = CreateResponseFrom(request);
        response->message = asprintf("%d", request->socketFd);
        response->Send(response);
        response = CreateResponseFrom(request);
        response->message = asprintf("%d %d", drone->mapTile->X, drone->mapTile->Y);
        response->Send(response);
        drone->status = READY;
    }
    else if (drone->status == READY) {
        Log(INFORMATION, "New command from client %d : %s", drone->socketFd, request->message);
        request->Parse(request);
        if (request->requestedAction == UNKNOWN_ACTION) {
            response = CreateKoResponseFrom(request);
            response->Send(response);
        }
        else
            drone->CommitRequest(drone, request);
    }
}

static void ExecuteRequests(ZappyServer *server) {
    server->world->drones->forEachElements(server->world->drones, lambda(void, (void *drone, void *dat), {
        ((Drone *)drone)->ExecutePendingRequest(drone);
    }), NULL);
}

static ZappyServer *Start(ZappyServer *server) {
    Request *request;
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    server->network = CreateNetwork(SERVER, (uint16_t) server->configuration->port, NULL);
    server->status = STARTED;
    Log(SUCCESS, "Zappy server started.");
    while (true) {
        request = server->network->Receive(server->network, &tv); //set timeout in function of next action timing
        if (request != NULL)
        {
            if (request->type == NEW_CLIENT) {
                NewClient(server, request);
            }
            else
                ExistingClient(server, request);
        }
        ExecuteRequests(server);
    }
    return server->ShutDown(server);
}

static Drone    *GetAssociatedDrone(Request *request, Map *map) {
    t_list *elem;

    elem = map->drones->firstElementFromPredicate(map->drones, lambda(bool, (void *drone, void *data), {
        if (((Drone *)drone)->socketFd == request->socketFd)
            return true;
        return false;
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        Log(ERROR, "Unable to bind request to existing drone.");
    return elem->data;
}

ZappyServer *CreateZappyServer() {
    ZappyServer *ret;

    ret = xmalloc(sizeof(ZappyServer));
    ret->status = UNINITIALIZED;
    ret->configuration = CreateConfiguration();
    ret->world = NULL;
    ret->teams = CreateLinkedList();
    ret->Configure = &Configure;
    ret->Start = &Start;
    ret->GetAssociatedDrone = &GetAssociatedDrone;
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