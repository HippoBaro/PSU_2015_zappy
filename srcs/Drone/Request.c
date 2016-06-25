//
// Created by barrauh on 6/25/16.
//

#include "ZappyServer.h"
#include "Drone.h"

static void ValidateAndStartRequestTimer(Drone *drone, Request *request)
{
    Response *response;

    if ((response = request->Validate(request, drone)) != NULL)
    {
        response->Send(response);
        drone->currentPendingRequest->Free(drone->currentPendingRequest);
        drone->currentPendingRequest = NULL;
        drone->ExecutePendingRequest(drone);
        return;
    }
    drone->currentPendingRequest->RequestDidBecomeActive(drone->currentPendingRequest, drone);
    drone->currentPendingRequest->timer = CreateAndStartTimer(request->GetCompletionTime(request, drone->mapTile->map->server));
}

static Drone *CommitRequest(Drone *drone, Request *request) {
    if (request != NULL && request->requestedAction == DIE)
        drone->Die(drone, request);
    else if (drone->currentPendingRequest != NULL &&
             drone->pendingRequests->countLinkedList(drone->pendingRequests) < 9)
        drone->pendingRequests->addElemFront(drone->pendingRequests, request);
    else if (drone->currentPendingRequest == NULL)
    {
        drone->currentPendingRequest = request;
        ValidateAndStartRequestTimer(drone, drone->currentPendingRequest);
    }
    return drone;
}

static void ExecuteCurrentPendingRequest(Drone *drone) {
    Response *response;

    if (drone->currentPendingRequest->timer->isElapsed(drone->currentPendingRequest->timer)) {
        Log(WARNING, "Executing action on drone %d. Action number is : %d. Suject is : %s", drone->socketFd, drone->currentPendingRequest->requestedAction, drone->currentPendingRequest->actionSubject);
        response = drone->currentPendingRequest->Execute(drone->currentPendingRequest, drone);
        if (response != NULL)
            response->Send(response);
        drone->currentPendingRequest->Free(drone->currentPendingRequest);
        drone->currentPendingRequest = NULL;
        drone->ExecutePendingRequest(drone);
    }
}

static Drone *ExecutePendingRequest(Drone *drone) {
    t_list *elem;

    if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) == 0)
        return drone;
    else if (drone->currentPendingRequest == NULL && drone->pendingRequests->countLinkedList(drone->pendingRequests) > 0) {
        elem = drone->pendingRequests->getElementFirst(drone->pendingRequests);
        drone->currentPendingRequest = elem->data;
        drone->pendingRequests->removeThisElem(drone->pendingRequests, elem);
        ValidateAndStartRequestTimer(drone, drone->currentPendingRequest);
    }
    if (drone->currentPendingRequest != NULL)
        drone->ExecuteCurrentPendingRequest(drone);
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
    selfDrone->ExecuteCurrentPendingRequest = &ExecuteCurrentPendingRequest;
}