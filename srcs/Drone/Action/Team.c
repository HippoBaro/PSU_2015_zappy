//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *GetTeamSlot(struct s_Drone *self, Request *request) {
    return CreateResponseFromFdWithMessage(self->socketFd, asprintf("%d",self->team->maxSlot - self->team->currentUsedSlot));
}