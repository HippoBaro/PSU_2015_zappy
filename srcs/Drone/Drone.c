//
// Created by barrauh on 6/12/16.
//

#include "Drone.h"

static void DestroyDrone(Drone *drone) {
    if (drone->team != NULL)
        free(drone);
    drone->inventory->freeAll(drone->inventory, NULL); //Todo set item destructor
    free(drone);
}

static void Move(struct e_Drone *self) {
    //todo Move Drone
}

static void Look(struct e_Drone *self) {
    //todo Look around
}

static void Rotate(struct e_Drone *self, Rotation rotation) {
    self->rotation = rotation;
}

static string ListInventory(struct e_Drone *self) {
    self->inventory->forEachElements(self->inventory, lambda(void *, (void *param), {

    }), NULL);
}

Drone   *CreateDrone() {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->inventory = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = NULL;

    ret->Free = &DestroyDrone;
}