//
// Created by barrauh on 6/11/16.
//

#include <ZappyServer.h>

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
    ret->Parse = &ParseRequest;
    ret->GetCompletionTime = &GetCompletionTime;
    ret->Free = &DestroyRequest;
    InitRequestTransaction(ret);
    return ret;
}