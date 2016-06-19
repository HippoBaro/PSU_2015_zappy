/*
** maptile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 19:14:56 2016 Christian Diaconu
** Last update Tue Jun 14 14:38:52 2016 Christian Diaconu
*/

#include <Map.h>
#include <Drone.h>

void        DestroyMapTile(MapTile *mapTile) {
    mapTile->drones->freeAll(mapTile->drones, (void (*)(void *)) &DestroyDrone);
    mapTile->drones->Free(mapTile->drones);
    mapTile->ressources->freeAll(mapTile->ressources, (void (*)(void *)) &DestroyItem);
    mapTile->ressources->Free(mapTile->ressources);
    xfree(mapTile, sizeof(MapTile));
}

static MapTile  *SeedLoot(MapTile *self) {
    int i;
    int loot;

    loot = asymetricRandMinMax(5, 1, 10);
    i = 0;
    while (i < loot) {
        self->AddRessource(self, CreateRandomItem());
        ++i;
    }
    return self;
}

static string ListContent(MapTile *self) { //todo refactor
    string ressources = NULL;
    string drones = NULL;
    string ret = NULL;
    bool isFirst;

    isFirst = true;
    if (self->ressources->countLinkedList(self->ressources) > 0)
        self->ressources->forEachElements(self->ressources, lambda(void, (void *param, void *t), {
            Item *item = (Item *) param;
            if (!isFirst)
                ressources = strappend(ressources, " ", FIRST);
            ressources = strappend(ressources, item->ToString(item), FIRST);
            isFirst = false;
        }), NULL);
    isFirst = true;
    if (self->drones->countLinkedList(self->drones) > 0)
        self->drones->forEachElements(self->drones, lambda(void, (void *param, void *t), {
            if (!isFirst)
                drones = strappend(drones, " ", FIRST);
            drones = strappend(drones, "player", FIRST);
            isFirst = false;
        }), NULL);
    if (ressources == NULL && drones == NULL)
        return strdup("");
    else if (ressources == NULL && drones != NULL) {
        ret = asprintf("%s", drones);
        xfree(drones, strlen(drones));
    }
    else if (ressources != NULL && drones == NULL) {
        ret = asprintf("%s", ressources);
        xfree(ressources, strlen(ressources));
    }
    else if (ressources != NULL && drones != NULL) {
        ret = asprintf("%s %s", ressources, drones);
        xfree(ressources, strlen(ressources));
        xfree(drones, strlen(drones));
    }
    return ret;
}

MapTile	    *CreateMapTile(Map *map, int X, int Y)
{
    MapTile	*tile;

    tile = xmalloc(sizeof(MapTile));

    tile->X = X;
    tile->Y = Y;
    tile->map = map;
    tile->drones = CreateLinkedList();
    tile->ressources = CreateLinkedList();
    tile->AddDrone = &add_refplayer;
    tile->CountDrones = &count_players;
    tile->CountRessources = &count_ressources;
    tile->AddRessource = &add_ressource;
    tile->GetRessource = &get_ressource;
    tile->DroneExist = &is_refplayer;
    tile->RemoveDrone = &remove_refplayer;
    tile->GetTopTile = &GetTopTile;
    tile->GetBottomTile = &GetBottomTile;
    tile->GetLeftTile = &GetLeftTile;
    tile->GetRightTile = &GetRightTile;
    tile->SeedLoot = &SeedLoot;
    tile->ListContent = &ListContent;
    tile->Free = &DestroyMapTile;
    return (tile);
}
