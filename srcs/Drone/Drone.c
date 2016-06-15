//
// Created by barrauh on 6/12/16.
//

#include <string.h>
#include <Response.h>
#include <MapTile.h>
#include <Map.h>
#include "Drone.h"

void DestroyDrone(Drone *drone) {
    if (drone->team != NULL)
        xfree(drone->team, strlen(drone->team));
    drone->inventory->freeAll(drone->inventory, (void (*)(void *)) &DestroyItem); //Todo set item destructor
    drone->inventory->Free(drone->inventory);
    xfree(drone, sizeof(Drone));
}

static void Move(struct e_Drone *self, struct s_map *map) {
    //todo <--> Communication with server
    self->mapTile = self->mapTile->GetTopTile(self, map);
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

static void Turn90DegreesLeft (struct e_Drone *self) {
    //todo <--> Communication with server
    if (self->rotation - 90 == 0)
        self->rotation = 270;
    else
        self->rotation -= 90;
}

static void Turn90DegreesRight (struct e_Drone *self) {
    //todo <--> Communication with server
    if (self->rotation + 90 == 360)
        self->rotation = 0;
    else
        self->rotation += 90;
}

static Response *Broadcast(struct e_Drone *self, string message) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->destination = EVERYBODY;
    ret->message = message;
    return ret;
}

Drone   *CreateDrone(struct s_map *world, int StartX, int StartY) {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->inventory = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = NULL;

    ret->Move = &Move;
    ret->Look = &Look;
    ret->Rotate = &Rotate;
    ret->Turn90DegreesLeft = &Turn90DegreesLeft;
    ret->Turn90DegreesRight = &Turn90DegreesRight;
    ret->ListInventory = &ListInventory;
    ret->Take = &Take;
    ret->Drop = &Drop;
    ret->Expulse = &Expulse;
    ret->Fork = &Fork;
    ret->Die = &Die;
    ret->Free = &DestroyDrone;

    ret->mapTile = world->GetTile(world, StartX, StartY);
    ret->rotation = TOP;

    return ret;
}