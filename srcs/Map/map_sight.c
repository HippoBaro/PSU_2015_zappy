/*
** map_sight.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/srcs/Map
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Mon Jun 13 19:54:16 2016 Christian Diaconu
** Last update Mon Jun 13 20:28:43 2016 Christian Diaconu
*/

#include "Map.h"

/* CAUTION !
**
** Those functions do not take in consideration the actual rotation of the player.
** There all based on the map it-self :
**
**				 TOP
**	LEFT			  X			RIGHT
**				BOTTOM
*/

MapTile		*GetTopTile(Map *world, MapTile *tile)
{
  int		X;

  if (tile->X == 0)
    X = world->X;
  else
    X = tile->X + 1;
  return (world->GetTile(world, X, tile->Y));
}

MapTile		*GetBottomTile(Map *world, MapTile *tile)
{
  int		X;

  if (tile->X == world->X)
    X = 0;
  else
    X = tile->X - 1;
  return (world->GetTile(world, X, tile->Y));
}

MapTile		*GetLeftTile(Map *world, MapTile *tile)
{
  int		Y;

  if (tile->Y = 0)
    Y = world->Y;
  else
    Y = Y - 1;
  return (world->GetTile(world, tile->X, Y));
}

MapTile		*GetRightTile(Map *world, MapTile *tile)
{
  int		Y;

  if (tile->Y == world->Y)
    Y = 0;
  else
    Y = Y + 1;
  return (world->GetTile(world, tile->X, Y));
}
