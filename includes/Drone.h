//
// Created by barrauh on 6/12/16.
//

#ifndef PSU_2015_ZAPPY_DRONE_H
#define PSU_2015_ZAPPY_DRONE_H

#include "LinkedList.h"

typedef struct e_Drone {
    string      team;
    LinkedList(Item)  *inventory;
    int         socketFd;
    Rotation    rotation;
    void        *mapTile;
    void        (*Move)(struct e_Drone *self);
    void        (*Look)(struct e_Drone *self);
    void        (*Rotate)(struct e_Drone *self, Rotation rotation);
    string      (*ListInventory)(struct e_Drone *self);
    void        (*Take)(struct e_Drone *self, void *item);
    void        (*Drop)(struct e_Drone *self, void *item);
    void        (*Expulse)(struct e_Drone *self);
    void        (*Fork)(struct e_Drone *self);
    void        (*Die)(struct e_Drone *self);
    void        *(*Broadcast)(struct e_Drone *self, string message);
    void        (*Free)(struct e_Drone *self);
}               Drone;

#endif //PSU_2015_ZAPPY_DRONE_H
