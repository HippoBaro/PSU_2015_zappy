//
// Created by barrauh on 6/12/16.
//

#include <string.h>
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
    self->mapTile->RemoveDrone(self->mapTile, self);
    self->mapTile = self->mapTile->GetTopTile(self, map);
    self->mapTile->AddDrone(self->mapTile, self);
}

static void GoTop(struct e_Drone *self, struct s_map *map) {
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
        {
            Log(INFORMATION, "Adding request to pendingRequests list");
            drone->pendingRequests->addElemFront(drone->pendingRequests, request);
        }
        else
        {
            Log(INFORMATION, "Queue is full");
            //todo correctly ignore request (queue is full).
        }

    }
    else
    {
        Log(INFORMATION, "First request");
        drone->currentPendingRequest = request;
        drone->currentPendingRequest->timer = CreateAndStartTimer(10000000); //10 secondes
        //todo set timer correctly
    }
    return drone;
}

static Drone *ExecutePendingRequest(Drone *drone) {
    t_list *elem;

    if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) == 0)
    {
        Log(INFORMATION, "Nothing to execute");
        return drone;
    }
    else if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) > 0) {
        Log(INFORMATION, "Pulling request from pendingRequests list");
        elem = drone->pendingRequests->getElementFirst(drone->pendingRequests);
        drone->currentPendingRequest = elem->data;
        drone->currentPendingRequest->timer = CreateAndStartTimer(10000000); //10 secondes
        drone->pendingRequests->removeThisElem(drone->pendingRequests, elem);
        //todo set timer correctly
    }
    else if (drone->currentPendingRequest != NULL) {
        if (drone->currentPendingRequest->timer->isElapsed(drone->currentPendingRequest->timer)) {
            Log(WARNING, "Executing action on drone %d. Action number is : %d", drone->socketFd,
                drone->currentPendingRequest->requestedAction);
            drone->currentPendingRequest->Free(drone->currentPendingRequest);
            drone->currentPendingRequest = NULL;
            //todo execute request, delete it and put the next one in currentPendingRequest
        }
    }
    return drone;
}

Drone   *CreateDrone() {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->inventory = CreateLinkedList();
    ret->pendingRequests = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = NULL;
    ret->life = 10;
    ret->level = 1;
    ret->status = NEW;

    ret->Move = &Move;
    ret->GoTop = &GoTop;
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
    ret->CommitRequest = &CommitRequest;
    ret->ExecutePendingRequest = &ExecutePendingRequest;
    ret->rotation = TOP;

    return ret;
}