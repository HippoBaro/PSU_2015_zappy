/*
** Map.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:53:51 2016 Christian Diaconu
** Last update Mon Jun 13 01:23:29 2016 Christian Diaconu
*/

#include "MapTile.h"

#ifndef _ZAPPY_MAPTILE_H_
# define _ZAPPY_MAPTILE_H_

typedef struct              s_map {
    int                     X;
    int                     Y;
    LinkedList(MapTitle)    *mapTiles;
    void                    (*Free)(struct s_map *self);
}                           Map;


/* map_gettile() in map.c */
MapTitle *map_gettile(Map *world, int X, int Y);

Map *CreateMap(int width, int height);

void DestroyMap(Map *map);

#endif
