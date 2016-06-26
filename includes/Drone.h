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

    Response    *(*Die)(struct s_Drone *self, Request *request);

    Drone       *(*DuplicateDrone)(struct s_Drone *existing_drone, struct s_map *world);
    void        (*DropInternal)(struct s_Drone *self, ItemType item, int quantity, bool destroyItem);
    void        (*Turn90DegreesLeft)(struct s_Drone *self);
    void        (*Turn90DegreesRight)(struct s_Drone *self);
    string      (*GetDroneSight)(struct s_Drone *self, struct s_map *map);
    struct s_Drone *(*CommitRequest)(struct s_Drone *drone, Request *request);
    struct s_Drone *(*ExecutePendingRequest)(struct s_Drone *drone);
    void        (*ExecuteCurrentPendingRequest)(struct s_Drone *drone);
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

typedef struct s_incant_table {
    int requestedLevel;
    int minimumDrones;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} t_inc_tbl;


//Validate
Response    *CanIncant(struct s_Drone *self, Request *request);
Response    *CanExpulse (Drone *self, Request *request);
Response    *CanTake (struct s_Drone *self, Request *request);
Response    *CanDrop (struct s_Drone *self, Request *request);
Response    *CanRotate(struct s_Drone *self, Request *request);

//Execute
Response    *Move(struct s_Drone *self, Request *request);
Response    *Look(struct s_Drone *self, Request *request);
Response    *Rotate(struct s_Drone *self, Request *request);
Response    *ListInventory(struct s_Drone *self, Request *request);
Response    *Take(struct s_Drone *self, Request *request);
Response    *Drop(struct s_Drone *self, Request *request);
Response    *Expulse(struct s_Drone *self, Request *request);
Response    *Fork(struct s_Drone *self, Request *request);
Response    *Broadcast(struct s_Drone *self, Request *request);
Response    *GetTeamSlot(struct s_Drone *self, Request *request);
Response    *Incant(struct s_Drone *self, Request *request);
Response    *Die (Drone *self, Request *request);

Drone       *DuplicateDrone(Drone *existing_drone, struct s_map *world);

//Internal
void        DropInternal(struct s_Drone *self, ItemType itemType, int quantity, bool destroyItem);
string      GetDroneSight(Drone *self, struct s_map *map);
Drone       *CreateDrone(Team *team);
void        DestroyDrone(Drone *drone);
void        InitDroneMove(Drone *selfDrone);
void        InitDroneRequest(Drone *selfDrone);

static const struct s_incant_table incantTable[] =
{
    { 2, 1, 1, 0, 0, 0, 0, 0 },
    { 3, 2, 1, 1, 1, 0, 0, 0 },
    { 4, 2, 2, 0, 1, 0, 2, 0 },
    { 5, 4, 1, 1, 2, 0, 1, 0 },
    { 6, 4, 1, 2, 1, 3, 0, 0 },
    { 7, 6, 1, 2, 3, 0, 1, 0 },
    { 8, 6, 2, 2, 2, 2, 2, 1 }
};

#endif //PSU_2015_ZAPPY_DRONE_H
