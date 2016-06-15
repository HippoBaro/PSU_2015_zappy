//
// Created by barrauh on 6/12/16.
//

#ifndef PSU_2015_ZAPPY_DRONE_H
#define PSU_2015_ZAPPY_DRONE_H

#include "LinkedList.h"
#include "Item.h"
#include "Response.h"

/* No include of Map.h --> declare to gcc that the type exists elsewhere */
struct s_map;

typedef struct e_Drone {
    string      team;
    LinkedList(Item)  *inventory;
    int         socketFd;
    Rotation    rotation;
    struct s_maptile        *mapTile;
    void        (*Move)(struct e_Drone *self, struct s_map *map);
    void        (*Look)(struct e_Drone *self);
    void        (*Turn90DegreesLeft)(struct e_Drone *self);
    void        (*Turn90DegreesRight)(struct e_Drone *self);
    void        (*Rotate)(struct e_Drone *self, Rotation rotation);
    string      (*ListInventory)(struct e_Drone *self);
    void        (*Take)(struct e_Drone *self, Item *item);
    void        (*Drop)(struct e_Drone *self, Item *item);
    void        (*Expulse)(struct e_Drone *self);
    void        (*Fork)(struct e_Drone *self);
    void        (*Die)(struct e_Drone *self);
    Response    *(*Broadcast)(struct e_Drone *self, string message);
    void        (*Free)(struct e_Drone *self);
}               Drone;

Drone   *CreateDrone(struct s_map *world, int StartX, int StartY);
void    DestroyDrone(Drone *drone);

#endif //PSU_2015_ZAPPY_DRONE_H
