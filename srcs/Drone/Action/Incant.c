//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *Incant(struct s_Drone *self, Request *request) {
    self->mapTile->drones->forEachElements(self->mapTile->drones, lambda(void, (void *drone, void *dat), {
        if (((Drone *)drone)->level == self->level)
            ((Drone *)drone)->level++;
    }), NULL);
    return NULL;
}