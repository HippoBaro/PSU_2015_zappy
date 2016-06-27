/*
** maptile_directions.c for Zappy in /home/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Wed Jun 15 12:12:37 2016 Christian Diaconu
** Last update Mon Jun 27 02:07:49 2016 Etienne Pasteur
*/

#include "MapSight.h"
#include "Generic.h"
#include "Drone.h"
#include "Map.h"

MapTile		*GetTopTile(Drone *this_drone, Map *map)
{
  if (this_drone->rotation == TOP)
    return (Math_GetTopTile(map, this_drone->mapTile));
  if (this_drone->rotation == RIGHT)
    return (Math_GetRightTile(map, this_drone->mapTile));
  if (this_drone->rotation == BOTTOM)
    return (Math_GetBottomTile(map, this_drone->mapTile));
  if (this_drone->rotation == LEFT)
    return (Math_GetLeftTile(map, this_drone->mapTile));
  return (NULL);
}

MapTile		*GetRightTile(Drone *this_drone, Map *map)
{
  if (this_drone->rotation == TOP)
    return (Math_GetRightTile(map, this_drone->mapTile));
  if (this_drone->rotation == RIGHT)
    return (Math_GetBottomTile(map, this_drone->mapTile));
  if (this_drone->rotation == BOTTOM)
    return (Math_GetRightTile(map, this_drone->mapTile));
  if (this_drone->rotation == LEFT)
    return (Math_GetBottomTile(map, this_drone->mapTile));
  return (NULL);
}

MapTile		*GetBottomTile(Drone *this_drone, Map *map)
{
  if (this_drone->rotation  == TOP)
    return (Math_GetBottomTile(map, this_drone->mapTile));
  if (this_drone->rotation == RIGHT)
    return (Math_GetLeftTile(map, this_drone->mapTile));
  if (this_drone->rotation == BOTTOM)
    return (Math_GetTopTile(map, this_drone->mapTile));
  if (this_drone->rotation == LEFT)
    return (Math_GetRightTile(map, this_drone->mapTile));
  return (NULL);
}

MapTile		*GetLeftTile(Drone *this_drone, Map *map)
{
  if (this_drone->rotation == TOP)
    return (Math_GetLeftTile(map, this_drone->mapTile));
  if (this_drone->rotation == RIGHT)
    return (Math_GetBottomTile(map, this_drone->mapTile));
  if (this_drone->rotation == BOTTOM)
    return (Math_GetLeftTile(map, this_drone->mapTile));
  if (this_drone->rotation == LEFT)
    return (Math_GetTopTile(map, this_drone->mapTile));
  return (NULL);
}
