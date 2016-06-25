//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *CanRotate(struct s_Drone *self, Request *request) {
    if (strcmp(request->actionSubject, "gauche") == 0)
        return NULL;
    else if (strcmp(request->actionSubject, "droite") == 0)
        return NULL;
    return CreateKoResponseFrom(request);
}