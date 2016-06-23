//
// Created by barrauh on 6/12/16.
//

#include <string.h>
#include <ZappyServer.h>
#include "Drone.h"

void DestroyDrone(Drone *drone) {
    drone->inventory->freeAll(drone->inventory, (void (*)(void *)) &DestroyItem);
    drone->inventory->Free(drone->inventory);
    drone->pendingRequests->freeAll(drone->pendingRequests, (void (*)(void *)) &DestroyRequest);
    drone->pendingRequests->Free(drone->pendingRequests);
    xfree(drone, sizeof(Drone));
}

static void Move(struct s_Drone *self, struct s_map *map) {
    self->mapTile->RemoveDrone(self->mapTile, self);
    self->mapTile = self->mapTile->GetTopTile(self, map);
    self->mapTile->AddDrone(self->mapTile, self);
}

static void GoTop(struct s_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetTopTile(self, map);
}

static void GoLeft(struct s_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetLeftTile(self, map);
}

static void GoRight(struct s_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetRightTile(self, map);
}

static void GoBackwards(struct s_Drone *self, struct s_map *map) {
    self->mapTile = self->mapTile->GetBottomTile(self, map);
}

static void Look(struct s_Drone *self) {
    //todo Look around
}

static void Rotate(struct s_Drone *self, Rotation rotation) {
    self->rotation = rotation;
}

static string ListInventory(struct s_Drone *self) { //todo refactor to tak into account quantity
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

static void Take (struct s_Drone *self, ItemType itemType) {
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

static void Drop (struct s_Drone *self, ItemType itemType, int quantity, bool destroyItem) {
    t_list *elem;

    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == itemType);
    }), NULL);
    if (elem != NULL && elem->data != NULL) {
        if (((Item *)elem->data)->quantity == 1)
        {
            self->inventory->removeThisElem(self->inventory, elem);
            if (!destroyItem)
                self->mapTile->AddRessource(self->mapTile, elem->data);
            else
            {
                Log (INFORMATION, "Freeying item from Drop()");
                self->inventory->freeThisElem(self->inventory, (void (*)(void *)) &DestroyItem, elem);
            }
        }
        else {
            ((Item *) elem->data)->quantity--;
            if (!destroyItem)
                self->mapTile->AddRessource(self->mapTile, CreateItemFrom(((Item *) elem->data)->type));
            self->Drop(self, itemType, --quantity, destroyItem);
        }
    }
}

static void Expulse (struct s_Drone *self) {
    //todo expulse drone from mapTile
}

static void Fork (struct s_Drone *self) {
    //todo fork
}

static void Die (struct s_Drone *self) {
    LinkedList(Drones) *drones;
    t_list *elem;
    t_list *elem2;

    if (self->team != NULL)
        self->team->currentUsedSlot--;
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
}

static void Turn90DegreesLeft (struct s_Drone *self) {
    if (self->rotation - 90 == 0)
        self->rotation = (Rotation) 270;
    else
        self->rotation -= 90;
}

static void Turn90DegreesRight (struct s_Drone *self) {
    if (self->rotation + 90 == 360)
        self->rotation = (Rotation) 0;
    else
        self->rotation += 90;
}

static Response *Broadcast(struct s_Drone *self, string message) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->message = message;
    //todo foreach drones, send message with correct tileNumber.
    return ret;
}

static Drone *CommitRequest(Drone *drone, Request *request) {
    if (request != NULL && request->requestedAction == DIE)
        drone->Die(drone);
    else if (drone->currentPendingRequest != NULL &&
        drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
            drone->pendingRequests->addElemFront(drone->pendingRequests, request);
    else if (drone->currentPendingRequest == NULL)
    {
        drone->currentPendingRequest = request;
        drone->currentPendingRequest->timer = CreateAndStartTimer(request->GetCompletionTime(request, drone->mapTile->map->server));
    }
    return drone;
}

static Drone *ExecutePendingRequest(Drone *drone) {
    t_list *elem;

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
            Log(WARNING, "Executing action on drone %d. Action number is : %d", drone->socketFd, drone->currentPendingRequest->requestedAction);
            drone->currentPendingRequest->Execute(drone->currentPendingRequest, drone);
            drone->currentPendingRequest->Free(drone->currentPendingRequest);
            drone->currentPendingRequest = NULL;
            drone->ExecutePendingRequest(drone);
        }
    }
    return drone;
}

//todo add ask slots

static bool UpdateLifeTime(Drone *drone) {
    uint64_t now;
    t_list *tList;
    Item *food;

    now = GetTimeNowAsUSec();
    if (drone->scheduledDeath == 0)
        return false;
    if (now >= drone->scheduledDeath) {
        tList = drone->inventory->firstElementFromPredicate(drone->inventory, lambda(bool, (void *elem, void *det), {
            return (bool)(((Item *)elem)->type == NOURRITURE);
        }), NULL);
        if (tList != NULL && (food = tList->data) != NULL) {
            drone->scheduledDeath = (uint64_t) (now + food->quantity + SecToUSec(food->quantity * drone->mapTile->map->server->configuration->temporalDelay) * 126);
            drone->Drop(drone, NOURRITURE, food->quantity, true);
        }
        else
            drone->Die(drone);
        return true;
    }
    return false;
}

Drone   *CreateDrone(Team *team) {
    Drone   *ret;

    ret = xmalloc(sizeof(Drone));
    ret->pendingRequests = CreateLinkedList();
    ret->inventory = CreateLinkedList();
    ret->mapTile = NULL;
    ret->team = team;
    ret->currentPendingRequest = NULL;
    ret->level = 1;
    ret->status = NEW;
    ret->scheduledDeath = (uint64_t) 0;

    ret->UpdateLifeTime = &UpdateLifeTime;
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