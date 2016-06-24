//
// Created by barrauh on 6/25/16.
//

#include "Generic.h"
#include "Drone.h"

static void Turn90DegreesLeft (struct s_Drone *self) {
    if (self->rotation - 90 == 0)
        self->rotation = (Rotation) 270;
    else
        self->rotation -= 90;
}

static void Turn90DegreesRight (struct s_Drone *self) {
    if (self->rotation + 90 == 360)
        self->rotation = (Rotation) 0;
    else
        self->rotation += 90;
}

Response *Move(struct s_Drone *self, Request *request) {
    self->mapTile->RemoveDrone(self->mapTile, self);
    self->mapTile = self->mapTile->GetTopTile(self, self->mapTile->map);
    self->mapTile->AddDrone(self->mapTile, self);
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

Response *Rotate(struct s_Drone *self, Request *request) {
    self->rotation = RIGHT; //todo parse request for direction
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

void InitDroneMove(Drone *selfDrone) {
    selfDrone->Turn90DegreesLeft = &Turn90DegreesLeft;
    selfDrone->Turn90DegreesRight = &Turn90DegreesRight;
    selfDrone->GoTop = lambda(void, (Drone *self, Map *map), {
        self->mapTile = self->mapTile->GetTopTile(self, map);
    });
    selfDrone->GoRight = lambda(void, (Drone *self, Map *map), {
        self->mapTile = self->mapTile->GetRightTile(self, map);
    });
    selfDrone->GoBackwards = lambda(void, (Drone *self, Map *map), {
        self->mapTile = self->mapTile->GetBottomTile(self, map);
    });
    selfDrone->GoLeft = lambda(void, (Drone *self, Map *map), {
        self->mapTile = self->mapTile->GetLeftTile(self, map);
    });
}