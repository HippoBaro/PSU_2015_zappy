//
// Created by barrauh on 6/12/16.
//

#include "Generic.h"
#include "Response.h"
#include <Network.h>

void        DestroyResponse(Response *response) {
    if (response->message != NULL)
        xfree(response->message, strlen(response->message));
    xfree(response, sizeof(Response));
}

//Create a response and populate the destination file descriptor with the one that the request came from.
Response    *CreateResponseFrom(Request *request) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->destFd = request->socketFd;
    return ret;
}

Response    *CreateResponseFromFdWithMessage(int fd, string message) {
    Response    *ret;

    ret = CreateEmptyResponse();
    ret->destFd = fd;
    ret->message = message;
    return ret;
}

Response    *CreateKoResponseFrom(Request *request) {
    Response    *ret;

    ret = CreateResponseFrom(request);
    ret->message = strdup("ko");
    return ret;
}

Response    *CreateEmptyResponse() {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = -1;
    ret->Send = lambda(bool, (Response *self), {
        self->message = strappend(self->message, "\n", FIRST);
        return Send(self);
    });
    ret->Free = &DestroyResponse;
    return ret;
}