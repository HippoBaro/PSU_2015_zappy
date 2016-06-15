//
// Created by barrauh on 6/13/16.
//

#include <zconf.h>

#include "ZappyServer.h"

static ZappyServer *Configure(ZappyServer *self, Configuration *config) {
    self->world = CreateMap(config->worldWidth, config->worldHeight);
    self->temporalDelay = config->temporalDelay;
    self->temporalDelay = config->temporalDelay;
    //todo create teams
    config->Free(config);
    Log(INFORMATION, "Server configured.");
    return self;
}

void DestroyZappyServer(ZappyServer *self) {
    self->teams->freeAll(self->teams, NULL); //todo set team destructor
    self->teams->Free(self->teams);
    self->world->Free(self->world);
    xfree(self, sizeof(ZappyServer));
    Log(INFORMATION, "Server was successfully destroyed.");
}

ZappyServer *CreateZappyServer() {
    ZappyServer *ret;

    ret = xmalloc(sizeof(ZappyServer));
    ret->world = NULL;
    ret->teams = CreateLinkedList();
    ret->Configure = &Configure;
    ret->Start = lambda(ZappyServer *, (ZappyServer *server), {
        Log(SUCCESS, "Zappy server started.");
        sleep(10);
        return server;
    });
    ret->Free = &DestroyZappyServer;
    Log(INFORMATION, "Server created.");
    return ret;
}