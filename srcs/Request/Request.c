//
// Created by barrauh on 6/11/16.
//

#include <ZappyServer.h>
#include "Drone.h"

static const struct s_request_invoke commands[] =
{
    {MOVE,           (void *(*)(void *, Request *)) &Move, NULL},
    {ROTATE,         (void *(*)(void *, Request *)) &Rotate, NULL},
    {LOOK,           (void *(*)(void *, Request *)) &Look, NULL},
    {LOOK_INVENTORY, (void *(*)(void *, Request *)) &ListInventory, NULL},
    {TAKE,           (void *(*)(void *, Request *)) &Take, NULL},
    {DROP,           (void *(*)(void *, Request *)) &Drop, NULL},
    {EXPULSE,        (void *(*)(void *, Request *)) &Expulse, NULL},
    {BROADCAST,      (void *(*)(void *, Request *)) &Broadcast, NULL},
    {INCANT,         (void *(*)(void *, Request *)) &Incant, NULL},
    {FORK,           (void *(*)(void *, Request *)) &Fork, NULL},
    {ASK_SLOT,       (void *(*)(void *, Request *)) &GetTeamSlot, NULL},
    {DIE,            (void *(*)(void *, Request *)) &Die, NULL}
};

static Response *Execute(Request *request, Drone *drone) { //todo refactor. THIS IS UGLY BUT I DON'T KNOW HOW TO DO IT DIFFERENTLY
    int i;

    i = 0;
    while (i <= 11) //todo validate request
    {
        if (request->requestedAction == commands[i].requestAction)
            return commands[i].invokeAction(drone, request);
        ++i;
    }
    return NULL;
}

static Request *RequestDidBecomeActive(Request *request, Drone *drone) {
    Response *res;

    if (request->requestedAction == INCANT)
    {
        res = CreateResponseFrom(request);
        res->message = asprintf("elevation en cours\nniveau actuel : %d", drone->level);
        res->Send(res);
    }
    return request;
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
    ret->Execute = (void *(*)(Request *, void *)) &Execute;
    ret->RequestDidBecomeActive = (Request *(*)(Request *, void *)) &RequestDidBecomeActive;
    ret->Sanitize = &Sanitize;
    ret->Free = &DestroyRequest;
    ret->Parse = &ParseRequest;
    ret->GetCompletionTime = &GetCompletionTime;
    //todo set Validate
    return ret;
}