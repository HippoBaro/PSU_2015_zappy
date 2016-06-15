/*
** Map.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:53:51 2016 Christian Diaconu
** Last update Mon Jun 13 01:23:29 2016 Christian Diaconu
*/

#ifndef _ZAPPY_MAP_H_
#define _ZAPPY_MAP_H_

#include "LinkedList.h"
#include "MapTile.h"

typedef struct          s_ZappyServer ZappyServer;

typedef struct	        s_map
{
    int		            X;
    int		            Y;
    ZappyServer         *server;
    LinkedList(MapTile) *mapTiles;

    /* Ptr FX */
    Map                 *(*SeedLoot)(struct s_map *self);
    MapTile             *(*GetTile)(struct s_map *world, int X, int Y);
    void                (*Free)(struct s_map *map);
}		                Map;


Map     *CreateMap(int width, int height);
void    DestroyMap(Map *map);

#endif
