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
    drone->pendingRequests->freeAll(drone->pendingRequests, (void (*)(void *)) &DestroyRequest);
    if (drone->currentPendingRequest != NULL)
        drone->currentPendingRequest->Free(drone->currentPendingRequest);
    xfree(drone, sizeof(Drone));
}

static void Move(struct e_Drone *self, struct s_map *map) {
    //todo <--> Communication with server
    self->mapTile = self->mapTile->GetTopTile(self, map);
}

static void GoLeft(struct e_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetLeftTile(self, map);
}

static void GoRight(struct e_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetRightTile(self, map);
}

static void GoBackwards(struct e_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetBottomTile(self, map);
}

static void Look(struct e_Drone *self) {
    //todo Look around
}

static void Rotate(struct e_Drone *self, Rotation rotation) {
    self->rotation = rotation;
}

static string ListInventory(struct e_Drone *self) { //todo refactor to tak into account quantity
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
    //self->
}

static void Turn90DegreesLeft (struct e_Drone *self) {
    //todo <--> Communication with server.
    if (self->rotation - 90 == 0)
        self->rotation = 270;
    else
        self->rotation -= 90;
}

static void Turn90DegreesRight (struct e_Drone *self) {
    //todo <--> Communication with server.
    if (self->rotation + 90 == 360)
        self->rotation = 0;
    else
        self->rotation += 90;
}

static Response *Broadcast(struct e_Drone *self, string message) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->message = message;
    //todo foreach drones, send message with correct tileNumber.
    return ret;
}

static Drone *CommitRequest(Drone *drone, Request *request) {
    if (drone->currentPendingRequest != NULL)
    {
        if (drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
            drone->pendingRequests->addElemFront(drone->pendingRequests, request);
        else{}
            //todo correctly ignore request (queue full).
    }
    else
        drone->currentPendingRequest = request;
    return drone;
}

static Drone *ExecutePendingRequest(Drone *drone) {
    if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) == 0)
        return drone;
    else if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) > 0) {
        drone->currentPendingRequest = drone->pendingRequests->getElementFirst(drone->pendingRequests)->data;
        //todo start countDown
    }
    else if (drone->currentPendingRequest != NULL) {
        //todo if request can be executed, execute it.
    }
    return drone;
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
    ret->GoRight = &GoRight; // useless
    ret->GoBackwards = &GoBackwards; // useless
    ret->GoLeft = &GoLeft; // useless
    ret->Look = &Look;
    ret->Rotate = &Rotate;
    ret->Turn90DegreesLeft = &Turn90DegreesLeft;
    ret->Turn90DegreesRight = &Turn90DegreesRight;
    ret->GetDroneSight = &GetDroneSight;
    ret->ListInventory = &ListInventory;
    ret->Take = &Take;
    ret->Drop = &Drop;
    ret->Expulse = &Expulse;
    ret->Fork = &Fork;
    ret->Die = &Die;
    ret->Free = &DestroyDrone;
    ret->rotation = TOP;

    return ret;
}