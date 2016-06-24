//
// Created by barrauh on 6/12/16.
//

#include <ZappyServer.h>
#include "Drone.h"

void DestroyDrone(Drone *drone) {
    drone->inventory->freeAll(drone->inventory, (void (*)(void *)) &DestroyItem);
    drone->inventory->Free(drone->inventory);
    drone->pendingRequests->freeAll(drone->pendingRequests, (void (*)(void *)) &DestroyRequest);
    drone->pendingRequests->Free(drone->pendingRequests);
    xfree(drone, sizeof(Drone));
}

Response *GetTeamSlot(struct s_Drone *self, Request *request) {
    return CreateResponseFromFdWithMessage(self->socketFd, asprintf("%d",self->team->maxSlot - self->team->currentUsedSlot));
}

Response *Incant(struct s_Drone *self, Request *request) {
    //todo Incant
    return NULL;
}

Drone   *CreateDrone(Team *team) {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->pendingRequests = CreateLinkedList();
    ret->inventory = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = team;
    ret->currentPendingRequest = NULL;
    ret->level = 1;
    ret->status = NEW;
    ret->scheduledDeath = (uint64_t) 0;
    ret->rotation = TOP;

    ret->Die = &Die;

    ret->DropInternal = &DropInternal;
    ret->GetDroneSight = &GetDroneSight;
    ret->Free = &DestroyDrone;
    InitDroneMove(ret);
    InitDroneRequest(ret);
    return ret;
}