/*
** map.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:17:28 2016 Christian Diaconu
** Last update Mon Jun 13 00:25:34 2016 Christian Diaconu
*/

#include "Map.h"

void DestroyMap(Map *map) {
    map->mapTiles->freeAll(map->mapTiles, (void (*)(void *)) &DestroyMapTile);
    map->mapTiles->Free(map->mapTiles);
    free(map);
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

    world->mapTiles = CreateLinkedList();
    while (i != width * height)
    {
        world->mapTiles->addElemEnd(world->mapTiles, CreateMapTitle(x, y));
        ++i;
        ++x;
        if (x >= width)
        {
            x = 0;
            ++y;
        }
    }
    return (world);
}

MapTitle *map_gettile(Map *world, int X, int Y) {
    t_list *ret;

    if (world == NULL)
        return (NULL);
    if (X > world->X || Y > world->Y)
        return (NULL);
    if ((ret = world->mapTiles->getElementAtPos(world->mapTiles, X * Y)) == NULL)
        return NULL;
    return ret->data;
}
