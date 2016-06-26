/*
** map_sight.c for in /home/diacon_c/PSU_2015_zappy/srcs/Map
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Mon Jun 13 19:54:16 2016 Christian Diaconu
** Last update Sun Jun 26 16:40:53 2016 Etienne Pasteur
*/

#include "Map.h"

MapTile	*Math_GetTopTile(Map *world, MapTile *tile)
{
  int	X;

  if (tile->X == 0)
    X = world->X - 1;
  else
    X = tile->X - 1;
  return (world->GetTile(world, X, tile->Y));
}

MapTile	*Math_GetBottomTile(Map *world, MapTile *tile)
{
  int	X;

  if (tile->X == (world->X - 1))
    X = 0;
  else
    X = tile->X + 1;
  return (world->GetTile(world, X, tile->Y));
}

MapTile	*Math_GetLeftTile(Map *world, MapTile *tile)
{
  int	Y;

  if (tile->Y == 0)
    Y = world->Y - 1;
  else
    Y = tile->Y - 1;
  return (world->GetTile(world, tile->X, Y));
}

MapTile	*Math_GetRightTile(Map *world, MapTile *tile)
{
  int	Y;

  if (tile->Y == (world->Y -1))
    Y = 0;
  else
    Y = tile->Y + 1;
  return (world->GetTile(world, tile->X, Y));
}
