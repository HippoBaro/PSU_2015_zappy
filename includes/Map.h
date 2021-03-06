/*
** Map.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:53:51 2016 Christian Diaconu
** Last update Mon Jun 27 00:08:31 2016 Etienne Pasteur
*/

#ifndef _ZAPPY_MAP_H_
# define _ZAPPY_MAP_H_

# include "LinkedList.h"
# include "MapTile.h"

typedef struct		s_ZappyServer ZappyServer;
typedef struct		s_Drone Drone;

typedef struct		s_map
{
    int			X;
    int			Y;
    ZappyServer		*server;
    LinkedList(MapTile)	*mapTiles;
    LinkedList(Drone)	*drones;
    struct s_map	*(*SeedLoot)(struct s_map *self);
    MapTile		*(*GetTile)(struct s_map *world, int X, int Y);
    MapTile		*(*GetRandomTile)(struct s_map *world);
    struct s_map	*(*AddDrone)(MapTile *tile, Drone *drone);
    struct s_map	*(*RemoveDrone)(struct s_map *world, Drone *drone);
    MapTile		*(*GetTileReceivingSound)(Drone *, Drone *, struct s_map *);
    int			(*GetTileNumberForDrone)(MapTile *, Drone *, struct s_map *);
    void		(*Free)(struct s_map *map);
}			Map;

void		InitMapSeed(Map *world);
void		InitMapDrone(Map *world);
Map		*CreateMap(ZappyServer *server, int width, int height);
void		DestroyMap(Map *map);

#endif
