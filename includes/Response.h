//
// Created by barrauh on 6/12/16.
//

#ifndef PSU_2015_ZAPPY_RESPONSE_H
#define PSU_2015_ZAPPY_RESPONSE_H

#include "Generic.h"
#include "Request.h"
#include "LinkedList.h"

typedef struct e_Response {
    Destination         destination;
    string              message;
    LinkedList(int)     *destFd;
    void                (*Send)(struct e_Response *self);
    void                (*Free)(struct e_Response *self);
}           Response;

Response    *CreateEmptyResponse();
Response    *CreateResponseFrom(Request *request);

#endif //PSU_2015_ZAPPY_RESPONSE_H
