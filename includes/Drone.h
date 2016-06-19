//
// Created by barrauh on 6/12/16.
//

#ifndef PSU_2015_ZAPPY_DRONE_H
#define PSU_2015_ZAPPY_DRONE_H

#include "LinkedList.h"
#include "Item.h"
#include "Response.h"
#include "Map.h"

typedef struct e_Drone {
    string      team;
    LinkedList(Item)    *inventory;
    LinkedList(Request) *pendingRequests;
    Request     *currentPendingRequest;
    DroneStatus status;
    int         life;
    int         level;
    int         socketFd;
    Rotation    rotation;
    struct s_maptile        *mapTile;

    void        (*Move)(struct e_Drone *self, Map *map);
    void        (*Look)(struct e_Drone *self);
    string      (*GetDroneSight)(struct e_Drone *self, struct s_map *map);
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
    struct e_Drone *(*CommitRequest)(struct e_Drone *drone, Request *request);
    struct e_Drone *(*ExecutePendingRequest)(struct e_Drone *drone);
    void        (*Free)(struct e_Drone *self);

    /*
     * Unfair functions that WILL NOT be use by the clients, for server only [internal purposes].
     *
     * IMPORTANT !
     * Those functions perform movement to jump tiles to tiles
     * But THERE WILL NOT update the Drone's presence on the Tile it self.
     * In other words, there only updates the 'drone->mapTile' pointer.
     */

    void        (*GoTop)(struct e_Drone *self, struct s_map *map);
    void        (*GoRight)(struct e_Drone *self, struct s_map *map);
    void        (*GoLeft)(struct e_Drone *self, struct s_map *map);
    void        (*GoBackwards)(struct e_Drone *self, struct s_map *map);

}               Drone;

string      GetDroneSight(Drone *self, struct s_map *map);
Drone       *CreateDrone();
void        DestroyDrone(Drone *drone);

#endif //PSU_2015_ZAPPY_DRONE_H
