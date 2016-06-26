//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

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
    if (self->level < 1 || self->level > 7)
        return CreateKoResponseFrom(request);
    else if (!CanIncantToLevel(self, self->mapTile, &(incantTable[self->level + 1])))
        return CreateKoResponseFrom(request);
    return NULL;
}