//
// Created by barrauh on 6/26/16.
//

#include "Map.h"

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

void    InitMapSeed(Map *world) {
    int i;
    int x;
    int y;

    i = x = y = 0;
    world->SeedLoot = &SeedLoot;
    while (i != world->X * world->Y) {
        world->mapTiles->addElemEnd(world->mapTiles, CreateMapTile(world, x, y));
        ++i;
        ++x;
        if (x >= world->X) {
            x = 0;
            ++y;
        }
    }
    world->SeedLoot(world);
}