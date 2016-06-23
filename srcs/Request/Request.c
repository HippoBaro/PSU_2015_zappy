//
// Created by barrauh on 6/11/16.
//

#include <ZappyServer.h>
#include "Request.h"
#include "Drone.h"

static Response *Execute(Request *request, Drone *drone) { //todo refactor. THIS IS UGLY BUT I DON'T KNOW HOW TO DO IT DIFFERENTLY
    if (request->requestedAction == UNKNOWN_ACTION)
        Log(ERROR, "Trying to execute unknown action");
    else if (request->requestedAction == TAKE)
        Log (INFORMATION, "Drone [%d] : Taking object %s", drone->socketFd, request->actionSubject);
    else if (request->requestedAction == DROP)
        Log (INFORMATION, "Drone [%d] : Droping object %s", drone->socketFd, request->actionSubject);
    else if (request->requestedAction == FORK)
        Log (INFORMATION, "Drone [%d] : Forking", drone->socketFd);
    else if (request->requestedAction == DIE)
        drone->Die(drone);
    else if (request->requestedAction == MOVE)
        drone->Move(drone, drone->mapTile->map);
    else if (request->requestedAction == ROTATE)
        Log (INFORMATION, "Drone [%d] : Rotation to %s", drone->socketFd, request->actionSubject);
    else if (request->requestedAction == LOOK_INVENTORY)
        Log (INFORMATION, "Drone [%d] : Look at inventory", drone->socketFd);
    else if (request->requestedAction == EXPULSE)
    Log (INFORMATION, "Drone [%d] : Expulse", drone->socketFd);
    else if (request->requestedAction == BROADCAST)
        Log (INFORMATION, "Drone [%d] : Broadcast %s", drone->socketFd, request->actionSubject);
    else if (request->requestedAction == INCANT)
        Log (INFORMATION, "Drone [%d] : Incanting", drone->socketFd);
    else if (request->requestedAction == ASK_SLOT)
        Log (INFORMATION, "Drone [%d] : Asking for slots status", drone->socketFd);
    else if (request->requestedAction == LOOK)
        Log (INFORMATION, "Drone [%d] : Look", drone->socketFd, request->actionSubject);
    return NULL; //todo return response correctly
}

static Request  *Sanitize(Request *self) {
    size_t len;

    if (self->message == NULL || (len = strlen(self->message)) == 0)
        return self;
    while (len > 0)
    {
        if (self->message[len] == '\n')
        {
            self->message[len] = '\0';
            return self;
        }
        --len;
    }
    return self;
}

static uint64_t GetCompletionTime(Request *self, ZappyServer *server) {
    double delayAsSeconds;
    uint64_t ret;

    delayAsSeconds = (double)self->absoluteActionTime * server->configuration->temporalDelay;
    Log(INFORMATION, "Request time is %lu", delayAsSeconds * 1000000);
    ret = (uint64_t) (delayAsSeconds * 1000000);
    return ret;
}

void    DestroyRequest(Request *request) {
    if (request->message != NULL)
        xfree(request->message, strlen(request->message) + 1);
    if (request->actionSubject != NULL)
        xfree(request->actionSubject, strlen(request->actionSubject));
    xfree(request->timer, sizeof(Timer));
    xfree(request, sizeof(Request));
}

Request *CreateRequest(string message, int socketFd) {
    Request *ret;

    ret = xmalloc(sizeof(Request));
    ret->type = UNKNOWN_REQUESTTYPE;
    ret->message = message;
    ret->socketFd = socketFd;
    ret->requestedAction = UNKNOWN_ACTION;
    ret->actionSubject = NULL;
    ret->timer = NULL;
    ret->absoluteActionTime = -1;
    ret->Execute = (void *(*)(struct t_Request *, void *)) &Execute;
    ret->Sanitize = &Sanitize;
    ret->Free = &DestroyRequest;
    ret->Parse = &ParseRequest;
    ret->GetCompletionTime = &GetCompletionTime;
    //todo set Validate
    return ret;
}