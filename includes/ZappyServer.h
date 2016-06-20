//
// Created by barrauh on 6/13/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYSERVER_H
#define PSU_2015_ZAPPY_ZAPPYSERVER_H

#include <Map.h>
#include "Network.h"

typedef struct              s_Configuration {
    int                     port;
    int                     worldHeight;
    int                     worldWidth;
    LinkedList(string)      *teamNames;
    int                     initialClientPerTeam;
    double                  temporalDelay;
    int                     *seed;
    struct s_Configuration  *(*Validate)(struct s_Configuration *self);
    struct s_Configuration  *(*ParseFrom)(struct s_Configuration *self, int ac, char **av);
    void                    (*Free)(struct s_Configuration *self);
}                           Configuration;

typedef struct              s_ZappyServer {
    ZappyServerStatus       status;
    Configuration           *configuration;
    Map                     *world;
    LinkedList(string)      *teams;
    Network                 *network;
    struct s_ZappyServer    *(*Configure)(struct s_ZappyServer *self, Configuration *config);
    struct s_ZappyServer    *(*Start)(struct s_ZappyServer *self);
    struct s_ZappyServer    *(*ShutDown)(struct s_ZappyServer *self);
    Drone                   *(*GetAssociatedDrone)(Request *self, Map *map);
    struct timeval          *(*GetNextRequestDelay)(struct s_ZappyServer *self);
    void                    (*Free)(struct s_ZappyServer *self);
}                           ZappyServer;

ZappyServer *CreateZappyServer();
void DestroyZappyServer(ZappyServer *self);

Configuration *CreateConfiguration();
void DestroyConfiguration(Configuration *config);

#endif //PSU_2015_ZAPPY_ZAPPYSERVER_H
