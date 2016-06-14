/*
** map_tileplayer.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 18:37:28 2016 Christian Diaconu
** Last update Tue Jun 14 10:12:59 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "MapTile.h"
#include "Drone.h"

#define    META_X            24
#define META_Y            42
#define RESSOURCES_TO_CREATE    5

<<<<<<< HEAD
void		create_players(MapTile *tile)
{
  int		i;

  i = 0;
  while (i != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Player (null) +1\n");
      tile->AddDrone(tile, NULL);
      i++;
    }
}

int		main()
{
  MapTile	*maptile;
  Drone		*player;

  maptile = CreateMapTile(META_X, META_Y);
  player = CreateDrone();
  if (maptile == NULL)
    {
      printf("	---> Creating a maptile : KO\n");
      return (-1);
=======
void create_players(MapTile *tile) {
    int i;

    i = 0;
    while (i != RESSOURCES_TO_CREATE) {
        printf("  ---> Player (null) +1\n");
        tile->AddDrone(tile, CreateDrone());
        i++;
    }
}

void testMapTileDrone() {
    MapTile *maptile;
    Drone *player;

    maptile = CreateMapTile(META_X, META_Y);
    player = CreateDrone();
    if (maptile == NULL) {
        printf("	---> Creating a maptile : KO\n");
        return;
>>>>>>> bd161459569a105cc2711e5391241e2bc068cde7
    }
    printf("  ---> Creating maptile : OK\n");
    if (maptile->X == META_X && maptile->Y == META_Y)
        printf("  ---> MapTile meta data: OK\n");
    else {
        printf("  ---> MapTile meta data : KO\n");
        return;
    }
<<<<<<< HEAD
  create_players(maptile);
  if (maptile->CountDrones(maptile) != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Player count : KO\n");
      return (-1);
    }
  else
    printf("  ---> Player count : OK\n");
  maptile->AddDrone(maptile, player);
  maptile->RemoveDrone(maptile, player);
  if (maptile->CountDrones(maptile) == (RESSOURCES_TO_CREATE))
    printf("  ---> Removing [1] player : OK\n");
  else
    {
      printf("  ---> Removing [1] player : KO\n");
      return (-1);
    }
  maptile->AddDrone(maptile, (void *)player);
  if (maptile->DroneExist(maptile, player) == (-1))
    {
      printf("  ---> Player exists ? : KO\n");
      return (-1);
    }
  else
    printf("  ---> Player exists ? : OK\n");
  //maptile->Free(maptile);
  free(player);
=======
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
>>>>>>> bd161459569a105cc2711e5391241e2bc068cde7
}
