#include <LinkedList.h>
#include "MapTile.h"
#include <Map.h>
#include <stdio.h>
#include <bits/stdio2.h>
#include <Drone.h>
#include "Sound.h"

void DestroyMap(Map *map) {
    Log(INFORMATION, "Destroying map");
    map->mapTiles->freeAll(map->mapTiles, (void (*)(void *)) &DestroyMapTile);
    map->mapTiles->Free(map->mapTiles);
    map->drones->freeAll(map->drones, (void (*)(void *)) &DestroyDrone);
    map->drones->Free(map->drones);
    xfree(map, sizeof(Map));
}

static MapTile *GetTile(Map *world, int X, int Y) {
    t_list  *ret;

    if (world == NULL)
        return (NULL);
    if (X > world->X || Y > world->Y)
        return (NULL);
    ret = world->mapTiles->firstElementFromPredicate(world->mapTiles, lambda(bool, (void *elem, void *dat), {
        if (((MapTile *) elem)->X == X &&
            ((MapTile *) elem)->Y == Y)
            return (true);
        return (false);
    }), NULL);
    if (ret == NULL)
        return NULL;
    return ret->data;
}

static Map  *SeedLoot(Map *self) {
    long totalItems;

    totalItems = 0;
    self->mapTiles->forEachElements(self->mapTiles, lambda(void, (void *tile, void *data), {
        if ((bool)randMinMax(0, 1) == true)
            ((MapTile *)tile)->SeedLoot(tile);
        totalItems += ((MapTile *)tile)->CountRessources(tile);
    }), NULL);
    Log(INFORMATION, "The map was successfully populated with %ld items", totalItems);

    return self;
}

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

static MapTile *GetRandomTile(Map *self) {
    t_list *elem;
    int x;
    int y;

    x = randMinMax(0, self->X - 1);
    y = randMinMax(0, self->Y - 1);
    elem = self->mapTiles->firstElementFromPredicate(self->mapTiles, lambda(bool, (void *tile, void *dat), {
        if (((MapTile *)tile)->X == x && ((MapTile *)tile)->Y == y)
            return true;
        return false;
    }), NULL);
    if (elem == NULL || elem->data == NULL)
        Log(ERROR, "Unable to select random MapTile. Response was NULL for coordinates %d, %d", x, y);
    return elem->data;
}

Map *CreateMap(ZappyServer *server, int width, int height) {
    Map *world;
    int i;
    int x;
    int y;

    Log(INFORMATION, "Creating map of size %d x %d and populating it with random resources...", width, height);
    i = x = y = 0;
    world = xmalloc(sizeof(Map));
    world->X = width;
    world->Y = height;
    world->server = server;
    world->Free = &DestroyMap;
    world->GetTile = &GetTile;
    world->SeedLoot = &SeedLoot;
    world->GetRandomTile = &GetRandomTile;
    world->AddDrone = &AddDrone;
    world->RemoveDrone = & RemoveDrone;
    world->mapTiles = CreateLinkedList();
    world->drones = CreateLinkedList();
    world->GetTileReceivingSound = &evaluate_sound_path;
    while (i != width * height) {
        world->mapTiles->addElemEnd(world->mapTiles, CreateMapTile(world, x, y));
        ++i;
        ++x;
        if (x >= width) {
            x = 0;
            ++y;
        }
    }
    world->SeedLoot(world);
    return (world);
}

