//
// Created by barrauh on 6/12/16.
//

#include "Request.h"
#include "Response.h"
#include "LinkedList.h"

Response    *CreateResponseFrom(Request *request) {
    Response    *ret;

    ret = xmalloc(sizeof(Response));
    ret->message = NULL;
    ret->destFd = CreateLinkedList();
    return ret;
}