//
// Created by diacon_c on 25/06/16.
//

#include "Map.h"
#include "Drone.h"
#include "Sound.h"
#include "MapSight.h"

int GetTileNumberForDrone(MapTile *targeted_tile, Drone *receiver, Map *world)
{
  Drone     *ghost;
  int       i;

  i = 1;
  ghost = receiver->DuplicateDrone(receiver, world);
  ghost->GoTop(ghost, world);
  while (ghost->mapTile != targeted_tile && i < 10)
  {
    if (i == 1)
      ghost->GoLeft(ghost, world);
    else if (i >= 2 && i <= 3)
      ghost->GoBackwards(ghost, world);
    if (i >= 4 && i <= 5)
      ghost->GoRight(ghost, world);
    else if (i >= 6 && i <= 7)
      ghost->GoTop(ghost, world);
    printf("[TILE] --> @%ix%i\n", ghost->mapTile->X, ghost->mapTile->Y);
    i++;
  }
  if (i <= 8)
    return (i);
  return (-1);
}
