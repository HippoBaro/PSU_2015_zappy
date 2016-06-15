//
// Created by barrauh on 6/12/16.
//

#include <string.h>
#include <Response.h>
#include "Drone.h"

void DestroyDrone(Drone *drone) {
    if (drone->team != NULL)
        xfree(drone->team, strlen(drone->team));
    drone->inventory->freeAll(drone->inventory, (void (*)(void *)) &DestroyItem); //Todo set item destructor
    drone->inventory->Free(drone->inventory);
    xfree(drone, sizeof(Drone));
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
    string ret = NULL;
    bool isFirst;

    isFirst = true;
    if (self->inventory->countLinkedList(self->inventory) > 0)
        self->inventory->forEachElements(self->inventory, lambda(void, (void *param, void *t), {
            Item *item = (Item *)param;
            if (!isFirst)
                ret = strappend(ret, ", ", FIRST);
            ret = strappend(ret, item->ToString(item), FIRST);
            isFirst = false;
        }), NULL);
    ret = strappend(ret, " }", FIRST);
    return strappend("{ ", ret, SECOND);
}

static void Take (struct e_Drone *self, Item *item) {
    //todo take item
}

static void Drop (struct e_Drone *self, Item *item) {
    //todo drop item
}

static void Expulse (struct e_Drone *self) {
    //todo expulse drone from mapTile
}

static void Fork (struct e_Drone *self) {
    //todo fork
}

static void Die (struct e_Drone *self) {
    //todo remove self from mapTile & Free self
}

static Response *Broadcast(struct e_Drone *self, string message) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->destination = EVERYBODY;
    ret->message = message;
    return ret;
}

Drone   *CreateDrone() {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->inventory = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = NULL;
    ret->life = 10;
    ret->level = 1;

    ret->Move = &Move;
    ret->Look = &Look;
    ret->Rotate = &Rotate;
    ret->ListInventory = &ListInventory;
    ret->Take = &Take;
    ret->Drop = &Drop;
    ret->Expulse = &Expulse;
    ret->Fork = &Fork;
    ret->Die = &Die;
    ret->Free = &DestroyDrone;

    return ret;
}