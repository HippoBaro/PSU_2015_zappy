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
#include "Item.h"
#include "LinkedList.h"
#include "Drone.h"

MapTitle *CreateMapTitle(int X, int Y) {
    MapTitle *tile;

    tile = xmalloc(sizeof(MapTitle));
    tile->X = X;
    tile->Y = Y;
    tile->drones = CreateLinkedList();
    tile->ressources = CreateLinkedList();
    return (tile);
}

void DestroyMapTile(MapTitle *map) {
    map->drones->freeAll(map->drones, (void (*)(void *)) &DestroyDrone);
    map->drones->Free(map->drones);
    map->ressources->freeAll(map->ressources, (void (*)(void *)) &DestroyItem);
    map->ressources->Free(map->ressources);
    free(map);
}
