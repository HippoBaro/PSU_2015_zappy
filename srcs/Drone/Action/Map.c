//
// Created by barrauh on 6/25/16.
//

#include "ZappyServer.h"
#include "Drone.h"

Response *Look(Drone *self, Request *request) {
    return CreateResponseFromFdWithMessage(self->socketFd, self->GetDroneSight(self, self->mapTile->map));;
}

Response *Expulse (Drone *self, Request *request) {
    self->mapTile->drones->forEachElements(self->mapTile->drones, lambda(void, (void *droneD, void *dat), {
        Drone *drone;

        if ((drone = droneD) == self)
            return;
        drone->mapTile->RemoveDrone(drone->mapTile, drone);
        drone->mapTile = drone->mapTile->GetTopTile(drone, drone->mapTile->map);
        drone->mapTile->AddDrone(drone->mapTile, drone);
        //todo send message to other clients.
    }), NULL);
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

Response *Fork (Drone *self, Request *request) {
    self->team->maxSlot++;
    return NULL;
}

Response *Broadcast(Drone *self, Request *request) {
    //todo create function to get number from TileMap in relation to player TileMap.
    //todo foreach drones, send message with correct tileNumber.
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

Response *Die (Drone *self, Request *request) {
    Response *res;
    LinkedList(Drones) *drones;
    t_list *elem;
    t_list *elem2;

    if (self->team != NULL)
        self->team->currentUsedSlot--;
    res = CreateResponseFromFdWithMessage(self->socketFd, strdup("mort"));
    res->Send(res);
    self->mapTile->map->server->network->Disconnect(self->mapTile->map->server->network, self->socketFd);
    drones = self->mapTile->map->drones;
    elem = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        Log(ERROR, "Unable to find Drone in map (Die)");
    drones->removeThisElem(drones, elem);
    drones = self->mapTile->drones;
    elem2 = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    if (elem2 == NULL || elem2->data == NULL)
        Log(ERROR, "Unable to find Drone in mapTile (Die)");
    drones->freeThisElem(drones, (void (*)(void *)) &DestroyDrone, elem2);
    Log(INFORMATION, "Drone is dead.");
    return NULL;
}