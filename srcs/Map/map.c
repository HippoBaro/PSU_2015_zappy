/*
** map.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Map
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:37:15 2016 Etienne Pasteur
** Last update Sun Jun 26 19:53:09 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "MapTile.h"
#include "Map.h"
#include "Drone.h"
#include "Sound.h"

void		DestroyMap(Map *map)
{
  Log(INFORMATION, "Destroying map");
  map->mapTiles->freeAll(map->mapTiles, (void (*)(void *)) &DestroyMapTile);
  map->mapTiles->Free(map->mapTiles);
  map->drones->freeAll(map->drones, (void (*)(void *)) &DestroyDrone);
  map->drones->Free(map->drones);
  xfree(map, sizeof(Map));
}

static MapTile	*GetRandomTile(Map *self)
{
  t_list	*elem;
  int		x;
  int		y;

  x = randMinMax(0, self->X - 1);
  y = randMinMax(0, self->Y - 1);
  elem = FirstPred(self->mapTiles, tile, {
	return (bool) (((MapTile *)tile)->X == x && ((MapTile *)tile)->Y == y);
      });
  if (elem == NULL || elem->data == NULL)
    Log(ERROR, "Unable to select random MapTile. Resulted in NULL at [%dx%d]",
	x, y);
  return (elem->data);
}

static MapTile	*GetTile(Map *world, int X, int Y)
{
  t_list	*ret;

  if (world == NULL)
    return (NULL);
  if (X > world->X || Y > world->Y)
    return (NULL);
  ret = FirstPred(world->mapTiles, elem, {
	return (bool) (((MapTile *) elem)->X == X &&
	    ((MapTile *) elem)->Y == Y);
      });
  if (ret == NULL)
    return (NULL);
  return (ret->data);
}

Map		*CreateMap(ZappyServer *server, int width, int height)
{
  Map		*world;

  Log(INFORMATION, "Creating map of size %dx%d, adding random resources...",
      width, height);
  world = xmalloc(sizeof(Map));
  world->X = width;
  world->Y = height;
  world->server = server;
  world->mapTiles = CreateLinkedList();
  world->drones = CreateLinkedList();
  world->Free = &DestroyMap;
  world->GetRandomTile = &GetRandomTile;
  world->GetTile = &GetTile;
  world->GetTileReceivingSound = &evaluate_sound_path;
  world->GetTileNumberForDrone = &GetTileNumberForDrone;
  InitMapSeed(world);
  InitMapDrone(world);
  return (world);
}
