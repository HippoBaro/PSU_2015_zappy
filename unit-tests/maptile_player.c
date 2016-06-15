/*
** map_tileplayer.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 18:37:28 2016 Christian Diaconu
** Last update Wed Jun 15 15:23:14 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "Map.h"
#include "Drone.h"

#define    META_X            24
#define META_Y            42
#define RESSOURCES_TO_CREATE    5

void create_players(Map *world, MapTile *tile) {
  int i;

  i = 0;
  while (i != RESSOURCES_TO_CREATE) {
    printf("  ---> Player (null) +1\n");
    tile->AddDrone(tile, CreateDrone(world, 0, 0));
    i++;
  }
}

void testMapTileDrone() {
  Map     *world;
  MapTile *maptile;
  Drone *player;

  world = CreateMap(5, 5);
  maptile = CreateMapTile(META_X, META_Y);
  player = CreateDrone(world, 0, 0);
  if (maptile == NULL) {
    printf("---> Creating a maptile : KO\n");
    return;
  }
  printf("  ---> Creating maptile : OK\n");
  if (maptile->X == META_X && maptile->Y == META_Y)
    printf("  ---> MapTile meta data: OK\n");
  else {
    printf("  ---> MapTile meta data : KO\n");
    return;
  }
  create_players(maptile);
  if (maptile->CountDrones(maptile) != RESSOURCES_TO_CREATE) {
    printf("  ---> Player count : KO\n");
    return;
  }
  else
    printf("  ---> Player count : OK\n");
  maptile->AddDrone(maptile, player);
  maptile->RemoveDrone(maptile, player);
  if (maptile->CountDrones(maptile) == (RESSOURCES_TO_CREATE))
    printf("  ---> Removing [1] player : OK\n");
  else {
    printf("  ---> Removing [1] player : KO\n");
    return;
  }
  maptile->AddDrone(maptile, player);
  if (!maptile->DroneExist(maptile, player)) {
    printf("  ---> Player exists ? : KO\n");
    return;
  }
  else
    printf("  ---> Player exists ? : OK\n");
  maptile->Free(maptile);
}

#if UNIT_TEST
void		TestEntryPoint()
{
  test_all_map();
}
#endif
