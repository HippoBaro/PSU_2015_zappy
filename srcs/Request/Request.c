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
    ret->type = UNKNOWN_REQUESTTYPE;
    ret->message = message;
    ret->socketFd = socketFd;
    ret->requestedAction = UNKNOWN_ACTION;
    ret->actionSubject = NULL;
    ret->Free = &DestroyRequest;
    ret->Parse = &ParseRequest;
    //todo set Validate

    return ret;
}