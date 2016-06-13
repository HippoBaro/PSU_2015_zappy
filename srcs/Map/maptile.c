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
#include "Drone.h"

void        DestroyMapTile(MapTile *map) {
    map->drones->freeAll(map->drones, (void (*)(void *)) &DestroyDrone);
    map->drones->Free(map->drones);
    map->ressources->freeAll(map->ressources, (void (*)(void *)) &DestroyItem);
    map->ressources->Free(map->ressources);
    free(map);
}

MapTile	    *CreateMapTile(int X, int Y)
{
  MapTile	*tile;

  if ((tile = malloc(sizeof(MapTile))) == NULL)
    return (NULL);

  tile->X = X;
  tile->Y = Y;
  tile->drones = CreateLinkedList();
  tile->ressources = CreateLinkedList();
  tile->AddDrone = &add_refplayer;
  tile->CountDrones = &count_players;
  tile->AddRessource = &add_ressource;
  tile->CountRessources = &count_ressources;
  tile->AddRessource = &add_ressource;
  tile->GetRessource = &get_ressource;
  tile->DroneExist = &is_refplayer;
  tile->RemoveDrone = &remove_refplayer;
  tile->Free = &DestroyMapTile;

  return (tile);
}


