/*
** ZappyServer.h for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:39:20 2016 Etienne Pasteur
** Last update Mon Jun 27 00:44:51 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_ZAPPYSERVER_H
# define PSU_2015_ZAPPY_ZAPPYSERVER_H

# include "Map.h"
# include "Network.h"
# include "Team.h"

typedef struct			s_Configuration
{
    int				port;
    int				worldHeight;
    int				worldWidth;
    LinkedList(string)		*teamNames;
    int				initialClientPerTeam;
    double			temporalDelay;
    int				*seed;
    struct s_Configuration	*(*Validate)(struct s_Configuration *self);
    struct s_Configuration	*(*ParseFrom)(struct s_Configuration *,
					      int, char **);
    void			(*Free)(struct s_Configuration *self);
}				Configuration;

typedef struct			s_ZappyServer
{
    ZappyServerStatus		status;
    Configuration		*configuration;
    Map				*world;
    LinkedList(Team)		*teams;
    Network			*network;
    struct timeval		*nextTimeout;
    struct s_ZappyServer	*(*Configure)(struct s_ZappyServer *, Configuration *);
    Team			*(*GetTeamFromTeamName)(struct s_ZappyServer *, string);
    struct s_ZappyServer	*(*Start)(struct s_ZappyServer *self);
    struct s_ZappyServer	*(*UpdateState)(struct s_ZappyServer *self);
    struct s_ZappyServer	*(*ShutDown)(struct s_ZappyServer *self);
    Drone			*(*GetAssociatedDrone)(Request *self, Map *map);
	void			(*InitialDialogue)(struct s_ZappyServer *, Request *request, Drone *drone);
    void			(*ExistingClient)(struct s_ZappyServer *, Request *);
    void			(*NewClient)(struct s_ZappyServer *, Request *);
    struct timeval		*(*GetNextRequestDelay)(struct s_ZappyServer *);
    void			(*ExecuteRequests)(struct s_ZappyServer *self);
    void			(*Free)(struct s_ZappyServer *self);
}				ZappyServer;

ZappyServer			*CreateZappyServer();
void				InitZappyServerDrone(ZappyServer *self);
void				InitZappyServerLifeCycle(ZappyServer *server);
void				InitZappyServerRequest(ZappyServer *server);
void				DestroyZappyServer(ZappyServer *self);
Configuration			*CreateConfiguration();
void				DestroyConfiguration(Configuration *config);

#endif //PSU_2015_ZAPPY_ZAPPYSERVER_H
