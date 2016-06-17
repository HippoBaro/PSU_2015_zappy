//
// Created by barrauh on 6/12/16.
//

#include "Request.h"
#include "Response.h"
#include "LinkedList.h"

void        DestroyResponse(Response *response) {
    if (response->message != NULL)
        xfree(response->message, strlen(response->message));
    xfree(response, sizeof(Response));
}

//Create a response and populate the destination file descriptor with the one that the request came from.
Response    *CreateResponseFrom(Request *request) {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = request->socketFd;
    ret->Free = &DestroyResponse;
    return ret;
}

Response    *CreateEmptyResponse() {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = -1;
    ret->Free = &DestroyResponse;
    return ret;
}