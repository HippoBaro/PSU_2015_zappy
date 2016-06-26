//
// Created by barrauh on 6/25/16.
//

#include "ZappyServer.h"
#include "Drone.h"

Response *Look(Drone *self, Request *request) {
    return CreateResponseFromFdWithMessage(self->socketFd, self->GetDroneSight(self, self->mapTile->map));
}

Response *Expulse (Drone *self, Request *request) {
    self->mapTile->drones->forEachElements(self->mapTile->drones, lambda(void, (void *droneD, void *dat), {
        Drone *drone;
        Response *res;
        if ((drone = droneD) == self)
            return;
        drone->mapTile->RemoveDrone(drone->mapTile, drone);
        drone->mapTile = self->mapTile->GetTopTile(self, drone->mapTile->map);
        drone->mapTile->AddDrone(drone->mapTile, drone);
        res = CreateResponseFromFdWithMessage(drone->socketFd, asprintf("deplacement: %d", self->mapTile->map->GetTileNumberForDrone(self->mapTile, drone, self->mapTile->map)));
        res->Send(res);
    }), NULL);
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

Response *Fork (Drone *self, Request *request) {
    self->team->maxSlot++;
    return NULL;
}

Response *Die (Drone *self, Request *request) {
    LinkedList(Drones) *drones;
    t_list *elem;
    t_list *elem2;

    if (self->team != NULL)
        self->team->currentUsedSlot--;
    Send(CreateResponseFromFdWithMessage(self->socketFd, strdup("mort")));
    self->mapTile->map->server->network->Disconnect(self->mapTile->map->server->network, self->socketFd);
    drones = self->mapTile->map->drones;
    elem = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    drones->removeThisElem(drones, elem);
    drones = self->mapTile->drones;
    elem2 = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    drones->freeThisElem(drones, (void (*)(void *)) &DestroyDrone, elem2);
    Log(INFORMATION, "Drone is dead.");
    return NULL;
}