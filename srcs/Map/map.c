#include <LinkedList.h>
#include "MapTile.h"
#include <Map.h>
#include <stdio.h>
#include <bits/stdio2.h>

static bool        sorting_maptile(void *maptile_list, void *maptile_test)
{
    if (((MapTile *) maptile_list)->X == ((MapTile *) maptile_test)->X &&
        ((MapTile *) maptile_list)->Y == ((MapTile *) maptile_test)->Y)
        return (true);
    return (false);
}

void DestroyMap(Map *map) {
    map->mapTiles->freeAll(map->mapTiles, (void (*)(void *)) &DestroyMapTile);
    map->mapTiles->Free(map->mapTiles);
    xfree(map, sizeof(Map));
}

static MapTile *GetTile(Map *world, int X, int Y) {
    MapTile *fake;
    t_list  *ret;

    fake = xmalloc(sizeof(MapTile));
    fake->X = X;
    fake->Y = Y;
    if (world == NULL)
        return (NULL);
    if (X > world->X || Y > world->Y)
        return (NULL);
    ret = world->mapTiles->firstElementFromPredicate(world->mapTiles, &sorting_maptile, (void *) fake);
    if (ret == NULL)
        return NULL;
    xfree(fake, sizeof(MapTile));
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

