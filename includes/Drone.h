//
// Created by barrauh on 6/12/16.
//

#ifndef PSU_2015_ZAPPY_DRONE_H
#define PSU_2015_ZAPPY_DRONE_H

#include "LinkedList.h"
#include "Item.h"
#include "Response.h"
#include "Map.h"
#include "Team.h"

typedef struct s_Drone {
    Team        *team;
    LinkedList(Item)    *inventory;
    LinkedList(Request) *pendingRequests;
    Request     *currentPendingRequest;
    DroneStatus status;
    int         level;
    int         socketFd;
    Rotation    rotation;
    struct s_maptile        *mapTile;
    uint64_t    scheduledDeath;


    bool        (*UpdateLifeTime)(struct s_Drone *self);
    void        (*Move)(struct s_Drone *self, Map *map);
    void        (*Look)(struct s_Drone *self);
    string      (*GetDroneSight)(struct s_Drone *self, struct s_map *map);
    void        (*Turn90DegreesLeft)(struct s_Drone *self);
    void        (*Turn90DegreesRight)(struct s_Drone *self);
    void        (*Rotate)(struct s_Drone *self, Rotation rotation);
    string      (*ListInventory)(struct s_Drone *self);
    void        (*Take)(struct s_Drone *self, ItemType item);
    void        (*Drop)(struct s_Drone *self, ItemType item, int quantity, bool destroyItem);
    void        (*Expulse)(struct s_Drone *self);
    void        (*Fork)(struct s_Drone *self);
    void        (*Die)(struct s_Drone *self);
    Response    *(*Broadcast)(struct s_Drone *self, string message);
    struct s_Drone *(*CommitRequest)(struct s_Drone *drone, Request *request);
    struct s_Drone *(*ExecutePendingRequest)(struct s_Drone *drone);
    void        (*Free)(struct s_Drone *self);

    /*
     * Unfair functions that WILL NOT be use by the clients, for server only [internal purposes].
     *
     * IMPORTANT !
     * Those functions perform movement to jump tiles to tiles
     * But THERE WILL NOT update the Drone's presence on the Tile it self.
     * In other words, there only updates the 'drone->mapTile' pointer.
     */

    void        (*GoTop)(struct s_Drone *self, struct s_map *map);
    void        (*GoRight)(struct s_Drone *self, struct s_map *map);
    void        (*GoLeft)(struct s_Drone *self, struct s_map *map);
    void        (*GoBackwards)(struct s_Drone *self, struct s_map *map);

}               Drone;

string      GetDroneSight(Drone *self, struct s_map *map);
Drone       *CreateDrone(Team *team);
void        DestroyDrone(Drone *drone);

#endif //PSU_2015_ZAPPY_DRONE_H
