//
// Created by barrauh on 6/12/16.
//

#include "Request.h"
#include "Response.h"
#include "LinkedList.h"

void        DestroyResponse(Response *response) {
    response->destFd->freeAll(response->destFd, NULL);
    response->destFd->Free(response->destFd);
    if (response->message != NULL)
        free(response->message);
    free(response);
}

//Create a response and populate the destination file descriptor with the one that the request came from.
Response    *CreateResponseFrom(Request *request) {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = CreateLinkedList();
    ret->destFd->addElemFront(ret->destFd, (int *)request->socketFd);
    ret->destination = SUBSET;
    ret->Free = &DestroyResponse;
    return ret;
}

Response    *CreateEmptyResponse() {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = CreateLinkedList();
    ret->Free = &DestroyResponse;
    return ret;
}