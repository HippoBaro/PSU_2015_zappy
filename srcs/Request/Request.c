//
// Created by barrauh on 6/11/16.
//

#include "Request.h"

static void    DestroyRequest(Request *request) {
    if (request->message != NULL) {
        free(request->message);
    }
    if (request->actionSubject != NULL) {
        free(request->actionSubject);
    }
    free(request);
}

Request *CreateRequest(string message, int socketFd) {
    Request *ret;

    ret = xmalloc(sizeof(Request));
    ret->message = message;
    ret->socketFd = socketFd;
    ret->requestedAction = UNKNOWN;
    ret->actionSubject = NULL;
    ret->Free = &DestroyRequest;
    //todo set Validate
    //todo set Parse

    return ret;
}