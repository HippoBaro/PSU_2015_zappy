/*
** maptile_directions.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Wed Jun 15 12:12:37 2016 Christian Diaconu
** Last update Sun Jun 26 20:58:14 2016 Christian Diaconu
*/

#include "MapSight.h"
#include "Generic.h"
#include "Drone.h"
#include "Map.h"

/*
** CAUTION !
**
** Do not attempt to modify this file, it normally just works fine.
** In any doubt of a bug, please contact the maintainer of this file.
** Black magic is only recommended for advised people and required must of the time ink & paper.
*/

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
