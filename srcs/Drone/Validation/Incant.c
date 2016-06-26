/*
** Incant.c for z in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Validation
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:29:03 2016 Etienne Pasteur
** Last update Sun Jun 26 15:35:33 2016 Etienne Pasteur
*/

#include "Drone.h"

static int CountDroneWithMinLevel(int minLevel, MapTile *tile)
{
  int ret;

  ret = 0;
  tile->ressources->forEachElements(tile->ressources,
				    lambda(void, (void *drone, void *dat), {
					if (((Drone *)drone)->level >= minLevel)
					  ret++;
				      }), NULL);
  return (ret);
}

static bool CanIncantToLevel(Drone *s, MapTile *tile, const t_inc_tbl *l)
{
  if (CountDroneWithMinLevel(l->requestedLevel - 1, tile) < l->minimumDrones)
    return (false);
  else if (tile->CountRessource(tile, LINEMATE) < l->linemate)
    return (false);
  else if (tile->CountRessource(tile, DERAUMERE) < l->deraumere)
    return (false);
  else if (tile->CountRessource(tile, SIBUR) < l->sibur)
    return (false);
  else if (tile->CountRessource(tile, MENDIANE) < l->mendiane)
    return (false);
  else if (tile->CountRessource(tile, PHIRAS) < l->phiras)
    return (false);
  else if (tile->CountRessource(tile, THYSTAME) < l->thystame)
    return (false);
  return (true);
}

Response *CanIncant(Drone *s, Request *request)
{
  if (s->level < 1 || s->level > 7)
    return CreateKoResponseFrom(request);
  else if (!CanIncantToLevel(s, s->mapTile, &(incantTable[s->level + 1])))
    return (CreateKoResponseFrom(request));
  return (NULL);
}
