/*
** map_tileplayer.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 18:37:28 2016 Christian Diaconu
** Last update Mon Jun 13 21:03:18 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "MapTile.h"
#include "Drone.h"

#define META_X			24
#define META_Y			42
#define RESSOURCES_TO_CREATE	5

void		create_resources(MapTile *tile)
{
  int		i;

  i = 0;
  while (i != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Ressource +1\n");
      add_ressource(tile, MENDIANE);
      i++;
    }
}

int		main()
{
  MapTile	*maptile;

  maptile = CreateMapTile(META_X, META_Y);
  if (maptile == NULL)
    {
      printf("---> Creating a maptile : KO\n");
      return (-1);
    }
  printf("  ---> Creating maptile : OK\n");
  if (maptile->X == META_X && maptile->Y == META_Y)
    printf("  ---> MapTile meta data: OK\n");
  else
    {
      printf("  ---> MapTile meta data : KO\n");
      return (-1);
    }
  create_resources(maptile);
  if (count_ressources(maptile) != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Ressource count : KO\n");
      return (-1);
    }
  else
    printf("  ---> Ressource count : OK\n");
  if (get_ressource(maptile, MENDIANE) != (-1))
    printf("  ---> Getting ressource : OK\n");
  else
    {
      printf("  ---> Getting ressource : KO\n");
      return (-1);
    }
  if (count_ressources(maptile) != (RESSOURCES_TO_CREATE - 1))
    {
      printf("  ---> Ressource count : KO\n");
      return (-1);
    }
  else
    printf("  ---> Ressource count : OK\n");
  maptile->Free(maptile);
}
