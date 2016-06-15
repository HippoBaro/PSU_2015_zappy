//
// Created by barrauh on 6/13/16.
//

#include <zconf.h>
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

static ZappyServer *Start(ZappyServer *server) {
    server->status = STARTED;
    Log(SUCCESS, "Zappy server started.");
    sleep(10);
    //todo this is were the main loop will live
    return server->ShutDown(server);
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