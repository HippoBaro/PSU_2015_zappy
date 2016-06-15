#include <LinkedList.h>
#include "MapTile.h"
#include <Map.h>
#include <stdio.h>
#include <bits/stdio2.h>

void DestroyMap(Map *map) {
    map->mapTiles->freeAll(map->mapTiles, (void (*)(void *)) &DestroyMapTile);
    map->mapTiles->Free(map->mapTiles);
    xfree(map, sizeof(Map));
}

static MapTile *GetTile(Map *world, int X, int Y) {
    t_list *ret;

    if (world == NULL)
        return (NULL);
    if (X > world->X || Y > world->Y)
        return (NULL);
    if ((ret = world->mapTiles->getElementAtPos(world->mapTiles, X * Y)) == NULL)
        return NULL;
    return ret->data;
}

Map *CreateMap(int width, int height) {
    Map *world;
    int i;
    int x;
    int y;

    i = x = y = 0;
    world = xmalloc(sizeof(Map));
    world->X = width;
    world->Y = height;
    world->Free = &DestroyMap;
    world->GetTile = &GetTile;

    world->mapTiles = CreateLinkedList();
    while (i != width * height) {
        world->mapTiles->addElemEnd(world->mapTiles, CreateMapTile(x, y));
        ++i;
        ++x;
        if (x >= width) {
            x = 0;
            ++y;
        }
    }

    Log(INFORMATION, "Created map of size WIDTH : %d and HEIGHT : %d", width, height);
    return (world);
}

