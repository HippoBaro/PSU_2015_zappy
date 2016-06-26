//
// Created by barrauh on 6/26/16.
//

#include "Drone.h"
#include "Map.h"

Map *AddDrone(MapTile *tile, Drone *drone) {
    drone->mapTile = tile;
    tile->map->drones->addElemFront(tile->map->drones, drone);
    tile->drones->addElemFront(tile->drones, drone);
    return tile->map;
}

Map *RemoveDrone(Map *map, Drone *drone) {
    t_list *element;

    element = drone->mapTile->drones->firstElementFromPredicate(drone->mapTile->drones, lambda(bool, (void *elem, void*data), {
        if (elem == drone)
            return true;
        return false;
    }), NULL);
    drone->mapTile->drones->freeThisElem(drone->mapTile->drones, (void (*)(void *)) &DestroyDrone, element);
    return map;
}

Map *DeleteDrone(Map *map, Drone *drone) {
    t_list *element;

    element = drone->mapTile->drones->firstElementFromPredicate(drone->mapTile->drones, lambda(bool, (void *elem, void*data), {
        if (elem == drone)
            return true;
        return false;
    }), NULL);
    drone->mapTile->drones->freeThisElem(drone->mapTile->drones, (void (*)(void *)) &DestroyDrone, element);
    element = map->drones->firstElementFromPredicate(map->drones, lambda(bool, (void *elem, void*data), {
        if (elem == drone)
            return true;
        return false;
    }), NULL);
    map->drones->freeThisElem(map->drones, (void (*)(void *)) &DestroyDrone, element);
    return map;
}

void    InitMapDrone(Map *world) {
    world->AddDrone = &AddDrone;
    world->RemoveDrone = & RemoveDrone;
}