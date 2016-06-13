/*
** maptile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 19:14:56 2016 Christian Diaconu
** Last update Mon Jun 13 01:44:34 2016 Christian Diaconu
*/

#include "MapTile.h"
#include "LinkedList.h"


t_maptile	*init_maptile(int X, int Y)
{
  t_maptile	*tile;

  if ((tile = malloc(sizeof(t_maptile))) == NULL)
    return (NULL);

  tile->X = X;
  tile->Y = Y;
  tile->players = CreateLinkedList();
  tile->ressources = CreateLinkedList();
  tile->AddRefPlayer = &add_refplayer;
  tile->CountPlayers = &count_players;
  tile->AddRessource = &add_ressource;
  tile->CountRessources = &count_ressources;
  tile->AddRessource = &add_ressource;
  tile->GetRessource = &get_ressource;
  tile->PlayerExists = &is_refplayer;
  tile->RemovePlayer = &remove_refplayer;
  tile->Free = &free_maptile;

  return (tile);
}

void		free_maptile(t_maptile *map)
{
  //LinkedListDestroy(map->ressources);
  //LinkedListDestroy(map->players);
  free(map);
}
