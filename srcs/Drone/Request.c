//
// Created by barrauh on 6/25/16.
//

#include "ZappyServer.h"
#include "Drone.h"

static Drone *CommitRequest(Drone *drone, Request *request) {
    if (request != NULL && request->requestedAction == DIE)
        drone->Die(drone, request);
    else if (drone->currentPendingRequest != NULL &&
             drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
        drone->pendingRequests->addElemFront(drone->pendingRequests, request);
    else if (drone->currentPendingRequest == NULL)
    {
        drone->currentPendingRequest = request;
        drone->currentPendingRequest->RequestDidBecomeActive(drone->currentPendingRequest, drone);
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
        drone->currentPendingRequest->RequestDidBecomeActive(drone->currentPendingRequest, drone);
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
            drone->DropInternal(drone, NOURRITURE, food->quantity, true);
        }
        else
            drone->Die(drone, NULL);
        return true;
    }
    return false;
}

void InitDroneRequest(Drone *selfDrone) {
    selfDrone->UpdateLifeTime = &UpdateLifeTime;
    selfDrone->CommitRequest = &CommitRequest;
    selfDrone->ExecutePendingRequest = &ExecutePendingRequest;
}