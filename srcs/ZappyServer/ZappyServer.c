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

static ZappyServer *Start(ZappyServer *server) {
    int i;

    i = 1;
    Log(SUCCESS, "Zappy server started.");
    while (i <= 31) {
        if (i != SIGKILL && i != SIGSTOP)
            signal(i, lambda(void, (int sig), {
                Log(WARNING, "Received signal. Interrupting server. Singal was : %s (SIG = %d)", strsignal(sig), sig);
                server->ShutDown(server);
                server->Free(server);
                exit(EXIT_SUCCESS);
            }));
        ++i;
    }
    sleep(10);
    return server->ShutDown(server);
}

ZappyServer *CreateZappyServer() {
    ZappyServer *ret;

    ret = xmalloc(sizeof(ZappyServer));
    ret->world = NULL;
    ret->teams = CreateLinkedList();
    ret->Configure = &Configure;
    ret->Start = &Start;
    ret->ShutDown = lambda(ZappyServer *, (ZappyServer *server), {
        Log(WARNING, "Shutting down ZappyServer");
        return server;
    });
    ret->Free = &DestroyZappyServer;
    Log(INFORMATION, "Server created.");
    return ret;
}