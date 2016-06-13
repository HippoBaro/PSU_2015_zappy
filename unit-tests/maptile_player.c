/*
** map_tileplayer.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 18:37:28 2016 Christian Diaconu
** Last update Mon Jun 13 16:29:46 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "MapTile.h"
#include "Player.h"

#define	META_X			24
#define META_Y			42
#define RESSOURCES_TO_CREATE	5

void		create_players(t_maptile *tile)
{
  int		i;

  i = 0;
  while (i != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Player (null) +1\n");
      tile->AddRefPlayer(tile, NULL);
      i++;
    }
}

int		main()
{
  t_maptile	*maptile;
  Drone		*player;

  maptile = init_maptile(META_X, META_Y);
  player = CreateDrone();
  if (maptile == NULL)
    {
      printf("	---> Creating a maptile : KO\n");
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
  create_players(maptile);
  if (maptile->CountPlayers(maptile) != RESSOURCES_TO_CREATE)
    {
      printf("  ---> Player count : KO\n");
      return (-1);
    }
  else
    printf("  ---> Player count : OK\n");
  maptile->AddRefPlayer(maptile, player);
  maptile->RemovePlayer(maptile, player);
  if (maptile->CountPlayers(maptile) == (RESSOURCES_TO_CREATE))
    printf("  ---> Removing [1] player : OK\n");
  else
    {
      printf("  ---> Removing [1] player : KO\n");
      return (-1);
    }
  maptile->AddRefPlayer(maptile, (void *)player);
  if (maptile->PlayerExists(maptile, player) == (-1))
    {
      printf("  ---> Player exists ? : KO\n");
      return (-1);
    }
  else
    printf("  ---> Player exists ? : OK\n");
  maptile->Free(maptile);
  free(player);
}
