/*
** maptile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 19:14:56 2016 Christian Diaconu
** Last update Tue Jun 14 14:38:52 2016 Christian Diaconu
*/

#include "MapTile.h"
#include "LinkedList.h"
#include "Drone.h"

void        DestroyMapTile(MapTile *mapTile) {
    mapTile->drones->freeAll(mapTile->drones, (void (*)(void *)) &DestroyDrone);
    mapTile->drones->Free(mapTile->drones);
    mapTile->ressources->freeAll(mapTile->ressources, (void (*)(void *)) &DestroyItem);
    mapTile->ressources->Free(mapTile->ressources);
    xfree(mapTile, sizeof(MapTile));
}

MapTile	    *CreateMapTile(int X, int Y)
{
  MapTile	*tile;

  tile = xmalloc(sizeof(MapTile));

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
  tile->GetTopTile = &GetTopTile;
  tile->GetBottomTile = &GetBottomTile;
  tile->GetLeftTile = &GetLeftTile;
  tile->GetRightTile = &GetRightTile;
  return (tile);
}
