//
// Created by barrauh on 6/11/16.
//

#include <ZappyServer.h>
#include "Drone.h"

static const struct s_request_invoke commands[] =
{
    {MOVE,           (void *(*)(void *, Request *)) &Move,                                   NULL},
    {ROTATE,         (void *(*)(void *, Request *)) &Rotate,  (void *(*)(void *, Request *)) &CanRotate},
    {LOOK,           (void *(*)(void *, Request *)) &Look,                                   NULL},
    {LOOK_INVENTORY, (void *(*)(void *, Request *)) &ListInventory,                          NULL},
    {TAKE,           (void *(*)(void *, Request *)) &Take,    (void *(*)(void *, Request *)) &CanTake},
    {DROP,           (void *(*)(void *, Request *)) &Drop,    (void *(*)(void *, Request *)) &CanDrop},
    {EXPULSE,        (void *(*)(void *, Request *)) &Expulse, (void *(*)(void *, Request *)) &CanExpulse},
    {BROADCAST,      (void *(*)(void *, Request *)) &Broadcast,                              NULL},
    {INCANT,         (void *(*)(void *, Request *)) &Incant,  (void *(*)(void *, Request *)) &CanIncant},
    {FORK,           (void *(*)(void *, Request *)) &Fork,                                   NULL},
    {ASK_SLOT,       (void *(*)(void *, Request *)) &GetTeamSlot,                            NULL},
    {DIE,            (void *(*)(void *, Request *)) &Die,                                    NULL}
};

static Response *Execute(Request *request, Drone *drone) {
    int i;

    i = 0;
    while (i <= 11)
    {
        if (request->requestedAction == commands[i].requestAction)
            return commands[i].invokeAction(drone, request);
        ++i;
    }
    return NULL;
}

static Response *Validate(Request *request, Drone *drone) {
    int i;

    i = 0;
    while (i <= 11)
    {
        if (request->requestedAction == commands[i].requestAction)
        {
            if (commands[i].invokeValidate != NULL)
                return commands[i].invokeValidate(drone, request);
        }
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
    ret->Validate = (void *(*)(struct t_Request *, void *)) &Validate;
    return ret;
}