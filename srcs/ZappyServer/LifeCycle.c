//
// Created by barrauh on 6/26/16.
//

#include "Drone.h"
#include "ZappyServer.h"

static ZappyServer *StartInternal(ZappyServer *server) {
    Request *request;

    server->network = CreateNetwork(SERVER, (uint16_t) server->configuration->port, NULL);
    server->status = STARTED;
    Log(SUCCESS, "Zappy server started.");
    while (true) {
        if (feof(stdin))
            break;
        request = server->network->Receive(server->network, server->nextTimeout = server->GetNextRequestDelay(server));
        ForEach(server->world->drones, drone, {
            ((Drone *)drone)->UpdateLifeTime(drone);
        });
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

void InitZappyServerLifeCycle(ZappyServer *server)
{
    server->Start = &Start;
}