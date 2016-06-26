/*
** Drone.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Map
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:35:49 2016 Etienne Pasteur
** Last update Sun Jun 26 16:36:56 2016 Etienne Pasteur
*/

#include "Drone.h"
#include "Map.h"

Map		*AddDrone(MapTile *tile, Drone *drone)
{
  drone->mapTile = tile;
  tile->map->drones->addElemFront(tile->map->drones, drone);
  tile->drones->addElemFront(tile->drones, drone);
  return (tile->map);
}

Map		*RemoveDrone(Map *map, Drone *drone)
{
  t_list	*element;

  element = FirstPred(drone->mapTile->drones, elem, {
        return (bool) (elem == drone);
      });
  drone->mapTile->drones->freeThisElem(drone->mapTile->drones, (void (*)(void *)) &DestroyDrone, element);
  return (map);
}

Map		*DeleteDrone(Map *map, Drone *drone)
{
  t_list	*element;

  element = FirstPred(drone->mapTile->drones, elem, {
        return  (bool)(elem == drone);
      });
  drone->mapTile->drones->freeThisElem(drone->mapTile->drones, (void (*)(void *)) &DestroyDrone, element);
  element = FirstPred(map->drones, elem, {
        return (bool) (elem == drone);
      });
  map->drones->freeThisElem(map->drones, (void (*)(void *)) &DestroyDrone, element);
  return map;
}

void		InitMapDrone(Map *world)
{
  world->AddDrone = &AddDrone;
  world->RemoveDrone = & RemoveDrone;
}
