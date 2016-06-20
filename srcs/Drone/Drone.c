//
// Created by barrauh on 6/12/16.
//

#include <string.h>
#include <ZappyServer.h>
#include "Drone.h"

void DestroyDrone(Drone *drone) {
    if (drone->team != NULL)
        xfree(drone->team, strlen(drone->team));
    drone->inventory->freeAll(drone->inventory, (void (*)(void *)) &DestroyItem);
    drone->inventory->Free(drone->inventory);
    drone->pendingRequests->freeAll(drone->pendingRequests, (void (*)(void *)) &DestroyRequest);
    xfree(drone, sizeof(Drone));
}

static void Move(struct e_Drone *self, struct s_map *map) {
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

static void Take (struct e_Drone *self, ItemType itemType) {
    Item *item;
    t_list *elem;

    item = self->mapTile->GetRessource(self->mapTile, itemType);
    if (item == NULL)
        return;
    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == itemType);
    }), NULL);
    if (elem != NULL && elem->data != NULL)
    {
        ((Item *)elem->data)->quantity++;
        item->Free(item);
    }
    else
        self->inventory->addElemFront(self->inventory, item);
}

static void Drop (struct e_Drone *self, ItemType itemType) {
    t_list *elem;

    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == itemType);
    }), NULL);
    if (elem != NULL && elem->data != NULL) {
        self->inventory->removeThisElem(self->inventory, elem);
        self->mapTile->AddRessource(self->mapTile, elem->data);
    }
    else
        Log(ERROR, "Trying to drop an item that the drone hasn't in its inventory.");
}

static void Expulse (struct e_Drone *self) {
    //todo expulse drone from mapTile
}

static void Fork (struct e_Drone *self) {
    //todo fork
}

static void Die (struct e_Drone *self) {
    LinkedList(Drones) *drones;
    t_list *elem;

    drones = self->mapTile->map->drones;
    elem = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        Log(ERROR, "Unable to find Drone in map (Die)");
    drones->removeThisElem(drones, elem);
    drones = self->mapTile->drones;
    elem = drones->firstElementFromPredicate(drones, lambda(bool, (void *drone, void *dat), {
        return (bool)(self->socketFd == ((Drone *)drone)->socketFd);
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        Log(ERROR, "Unable to find Drone in mapTile (Die)");
    drones->freeThisElem(drones, (void (*)(void *)) &DestroyDrone, elem);
    Log(INFORMATION, "Drone is dead.");
}

static void Turn90DegreesLeft (struct e_Drone *self) {
    if (self->rotation - 90 == 0)
        self->rotation = 270;
    else
        self->rotation -= 90;
}

static void Turn90DegreesRight (struct e_Drone *self) {
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
    if (drone->currentPendingRequest != NULL &&
        drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
            drone->pendingRequests->addElemFront(drone->pendingRequests, request);
    else
    {
        drone->currentPendingRequest = request;
        drone->currentPendingRequest->timer = CreateAndStartTimer(request->GetCompletionTime(request, drone->mapTile->map->server));
    }
    return drone;
}

static Drone *ExecutePendingRequest(Drone *drone) {
    t_list *elem;

    if (drone->UpdateLifeTime(drone))
        return drone;
    if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) == 0)
        return drone;
    else if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) > 0) {
        elem = drone->pendingRequests->getElementFirst(drone->pendingRequests);
        drone->currentPendingRequest = elem->data;
        drone->currentPendingRequest->timer = CreateAndStartTimer(drone->
                currentPendingRequest->GetCompletionTime(drone->currentPendingRequest, drone->mapTile->map->server));
        drone->pendingRequests->removeThisElem(drone->pendingRequests, elem);
    }
    if (drone->currentPendingRequest != NULL) {
        if (drone->currentPendingRequest->timer->isElapsed(drone->currentPendingRequest->timer)) {
            Log(WARNING, "Executing action on drone %d. Action number is : %d", drone->socketFd,
                drone->currentPendingRequest->requestedAction);
            drone->currentPendingRequest->Execute(drone->currentPendingRequest, drone);
            drone->currentPendingRequest->Free(drone->currentPendingRequest);
            drone->currentPendingRequest = NULL;
            drone->ExecutePendingRequest(drone);
        }
    }
    return drone;
}

static bool UpdateLifeTime(Drone *drone) {
    uint64_t now;
    t_list *elem;

    now = TimeNowAsUSec();
    if (now - drone->lastUpdate > SecToUSec(1 * drone->mapTile->map->server->configuration->temporalDelay))
    {
        elem = drone->inventory->firstElementFromPredicate(drone->inventory, lambda(bool, (void *item, void *dat), {
            return (bool)(((Item *)item)->type == NOURRITURE);
        }), NULL);
        if (elem != NULL && elem->data != NULL && ((Item *)elem->data)->quantity > 0)
            drone->Drop(drone, NOURRITURE);
        else
        {
            drone->Die(drone);
            return true;
        }
    }
    return false;
}

static uint64_t GetLifeTimeLeft(Drone *drone) {
    t_list *elem;

    elem = drone->inventory->firstElementFromPredicate(drone->inventory, lambda(bool, (void *item, void *dat), {
        return (bool)(((Item *)item)->type == NOURRITURE);
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        return TimeNowAsUSec();
    return (uint64_t) (TimeNowAsUSec() + SecToUSec(((Item *)elem->data)->quantity * 1));
}

Drone   *CreateDrone() {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->inventory = CreateLinkedList();
    ret->inventory->addElemFront(ret->inventory, CreateItemWithQuantity(NOURRITURE, 10));
    ret->pendingRequests = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = NULL;
    ret->level = 1;
    ret->status = NEW;
    ret->lastUpdate = TimeNowAsUSec();

    ret->UpdateLifeTime = &UpdateLifeTime;
    ret->GetLifeTimeLeft = &GetLifeTimeLeft;
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