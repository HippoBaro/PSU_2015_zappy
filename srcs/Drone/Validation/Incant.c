//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

static const struct s_incant_table incantTable[] =
{
    { 2, 1, 1, 0, 0, 0, 0, 0 },
    { 3, 2, 1, 1, 1, 0, 0, 0 },
    { 4, 2, 2, 0, 1, 0, 2, 0 },
    { 5, 4, 1, 1, 2, 0, 1, 0 },
    { 6, 4, 1, 2, 1, 3, 0, 0 },
    { 7, 6, 1, 2, 3, 0, 1, 0 },
    { 8, 6, 2, 2, 2, 2, 2, 1 }
};

static int CountDroneWithMinLevel(int minLevel, MapTile *tile) {
    int ret;

    ret = 0;
    tile->ressources->forEachElements(tile->ressources, lambda(void, (void *drone, void *dat), {
        if (((Drone *)drone)->level >= minLevel)
            ret++;
    }), NULL);
    return ret;
}

static bool CanIncantToLevel(Drone *self, MapTile *tile, const struct s_incant_table *level) {
    if (CountDroneWithMinLevel(level->requestedLevel - 1, tile) < level->minimumDrones)
        return false;
    else if (tile->CountRessource(tile, LINEMATE) < level->linemate)
        return false;
    else if (tile->CountRessource(tile, DERAUMERE) < level->deraumere)
        return false;
    else if (tile->CountRessource(tile, SIBUR) < level->sibur)
        return false;
    else if (tile->CountRessource(tile, MENDIANE) < level->mendiane)
        return false;
    else if (tile->CountRessource(tile, PHIRAS) < level->phiras)
        return false;
    else if (tile->CountRessource(tile, THYSTAME) < level->thystame)
        return false;
    return true;
}

Response *CanIncant(Drone *self, Request *request) {
    struct s_incant_table *level;

    if (self->level < 1 || self->level > 7)
        return CreateKoResponseFrom(request);
    else if (!CanIncantToLevel(self, self->mapTile, &(incantTable[self->level + 1])))
        return CreateKoResponseFrom(request);
    return NULL;
}