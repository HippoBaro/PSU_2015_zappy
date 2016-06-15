//
// Created by barrauh on 6/13/16.
//

#ifndef PSU_2015_ZAPPY_ZAPPYSERVER_H
#define PSU_2015_ZAPPY_ZAPPYSERVER_H

#include <Map.h>

typedef struct              s_Configuration {
    int                     port;
    int                     worldHeight;
    int                     worldWidth;
    LinkedList(string)      *teamNames;
    int                     initialClientPerTeam;
    int                     temporalDelay;
    struct s_Configuration  *(*Validate)(struct s_Configuration *self);
    struct s_Configuration  *(*ParseFrom)(struct s_Configuration *self, int ac, char **av);
    void                    (*Free)(struct s_Configuration *self);
}                           Configuration;

typedef struct              s_ZappyServer {
    Map                     *world;
    LinkedList(string)      *teams;
    int                     temporalDelay;
    struct s_ZappyServer    *(*Configure)(struct s_ZappyServer *self, Configuration *config);
    struct s_ZappyServer    *(*Start)(struct s_ZappyServer *self);
    struct s_ZappyServer    *(*ShutDown)(struct s_ZappyServer *self);
    void                    (*Free)(struct s_ZappyServer *self);
}                           ZappyServer;

ZappyServer *CreateZappyServer();
void DestroyZappyServer(ZappyServer *self);

Configuration *CreateConfiguration();
void DestroyConfiguration(Configuration *config);

#endif //PSU_2015_ZAPPY_ZAPPYSERVER_H
