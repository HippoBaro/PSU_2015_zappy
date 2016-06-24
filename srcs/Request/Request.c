//
// Created by barrauh on 6/11/16.
//

#include <ZappyServer.h>
#include "Request.h"
#include "Drone.h"

static const struct s_request_invoke requestsArray[] =
{
        {MOVE,      (void *(*)(Request *, void *)) &Move},
        {ROTATE,      (void *(*)(Request *, void *)) &Rotate},
        {LOOK,        (void *(*)(Request *, void *)) &Look},
        {LOOK_INVENTORY,  (void *(*)(Request *, void *)) &ListInventory},
        {TAKE,       (void *(*)(Request *, void *)) &Take},
        {DROP,        (void *(*)(Request *, void *)) &Drop},
        {EXPULSE,     (void *(*)(Request *, void *)) &Expulse},
        {BROADCAST,   (void *(*)(Request *, void *)) &Broadcast},
        {INCANT, (void *(*)(Request *, void *)) &Incant},
        {FORK,        (void *(*)(Request *, void *)) &Fork},
        {ASK_SLOT, (void *(*)(Request *, void *)) &GetTeamSlot},
        {DIE,           (void *(*)(Request *, void *)) &Die}
};

static Response *Execute(Request *request, Drone *drone) { //todo refactor. THIS IS UGLY BUT I DON'T KNOW HOW TO DO IT DIFFERENTLY

    return NULL; //todo return response correctly
}

/*
 * This gets called when the request's Timer is started.
 * The request HAS been Validated.
 */
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