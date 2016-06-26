/*
** Seed.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Map
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:41:17 2016 Etienne Pasteur
** Last update Sun Jun 26 16:43:33 2016 Etienne Pasteur
*/

#include "Map.h"

static Map	*SeedLoot(Map *self)
{
  long		totalItems;

  totalItems = 0;
    ForEach(self->mapTiles, tile, {
				      if ((bool)randMinMax(0, 1) == true)
					((MapTile *)tile)->SeedLoot(tile);
				      totalItems += ((MapTile *)tile)->CountRessources(tile);
				    });
  Log(INFORMATION, "The map was successfully populated with %ld items",
      totalItems);
  return (self);
}

void		InitMapSeed(Map *wrd)
{
  int		i;
  int		x;
  int		y;

  i = x = y = 0;
  wrd->SeedLoot = &SeedLoot;
  while (i != wrd->X * wrd->Y)
    {
      wrd->mapTiles->addElemEnd(wrd->mapTiles, CreateMapTile(wrd, x, y));
      ++i;
      ++x;
      if (x >= wrd->X)
	{
	  x = 0;
	  ++y;
	}
    }
  wrd->SeedLoot(wrd);
}
