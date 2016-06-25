//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *CanExpulse (Drone *self, Request *request) {
    bool canExpulse;

    canExpulse = false;
    self->mapTile->drones->forEachElements(self->mapTile->drones, lambda(void, (void *droneD, void *dat), {
        if (droneD == self)
            return;
        canExpulse = true;
    }), NULL);
    if (canExpulse)
        return NULL;
    return CreateKoResponseFrom(request);
}