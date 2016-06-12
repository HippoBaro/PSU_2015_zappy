//
// Created by barrauh on 6/12/16.
//

#include "Request.h"
#include "Response.h"
#include "LinkedList.h"

void        DestroyResponse(Response *response) {
    response->destFd->freeAll(response->destFd, NULL);
    if (response->message != NULL)
        free(response->message);
    free(response);
}

Response    *CreateResponseFrom(Request *request) {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = CreateLinkedList();
    ret->Free = &DestroyResponse;
    return ret;
}