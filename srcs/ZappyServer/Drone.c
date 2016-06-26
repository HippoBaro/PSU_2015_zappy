//
// Created by barrauh on 6/26/16.
//

#include "Drone.h"
#include "ZappyServer.h"

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

static Drone    *GetAssociatedDrone(Request *request, Map *map) {
    t_list *elem;

    elem = FirstPred(map->drones, drone, {
        return (bool) (((Drone *)drone)->socketFd == request->socketFd);
    });
    if (elem == NULL || elem->data == NULL)
        return NULL;
    return elem->data;
}

void InitZappyServerDrone(ZappyServer *server)
{
    server->GetAssociatedDrone = &GetAssociatedDrone;
    server->ExistingClient = &ExistingClient;
    server->NewClient = &NewClient;
}