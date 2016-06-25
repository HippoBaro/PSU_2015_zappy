/*
** maptile_player_sight.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/srcs/Map
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Wed Jun 15 20:07:17 2016 Christian Diaconu
** Last update Wed Jun 15 20:10:16 2016 Christian Diaconu
*/

#include "LinkedList.h"
#include "Drone.h"
#include "Map.h"

#define DEBUG   false

static Drone    *DuplicateDrone(Drone *existing_drone, Map *world)
{
    Drone       *fake;

    fake = CreateDrone(existing_drone->team);
    fake->rotation = existing_drone->rotation;
    fake->mapTile = existing_drone->mapTile;
    fake->team = existing_drone->team;
    fake->level = existing_drone->level;

    /* if at creation this duplicated drone is referenced on tile, removing it. */
    fake->mapTile->RemoveDrone(fake->mapTile, fake);

    return (fake);
}

static string GetRessourcesAsStringOnSightOnLength(Drone *player, Map *world, int row_length)
{
    string      answer;
    int         i;

    i = 0;

    answer = NULL;
    while (i < (row_length))
    {
        if (DEBUG == true)
            printf(" --> TILE : @%ix%i  [%i --> %i]\n", player->mapTile->X, player->mapTile->Y, i, row_length);
        if (i != 0)
            answer = asprintf("%s, %s", answer, player->mapTile->ListContent(player->mapTile));
        else
            answer = asprintf("%s", player->mapTile->ListContent(player->mapTile));
        player->GoRight(player, world);
        i++;
    }
    if (DEBUG == true)
        printf("\n");
    return (answer);
}


static string GetRessourceOnSightAtLevel(Drone *player, Map *world, int level_n)
{
    string  function_answer;
    Drone   *drone_forked;
    int     i;

    if (DEBUG == true)
        printf("--> GETTING LEVEL [%i] :\n", level_n);

    /*
     * The drone "player" is defined by a pointer and is now at the right level in the column,
     * in other words in a row witch is in the same column as the starting row.
     *
     * Because "player" is a pointer and this pointer will be used for further analysis, we do
     * not want to modify it's ideal and actual location, this is why duplicating it.
     */

    i = 0;
    drone_forked = DuplicateDrone(player, world);

    // Putting the cloned "Drone" at beginning of the row's line, before starting analysis.
    while (i < level_n)
    {
        drone_forked->GoLeft(drone_forked, world);
        i++;
    }
    function_answer = GetRessourcesAsStringOnSightOnLength(drone_forked, world, (level_n * 2) + 1);
    xfree(drone_forked, sizeof(Drone));
    return (function_answer);
}

string         GetDroneSight(Drone *player, Map *world)
{
    string      answer;
    string      temp;
    Drone       *new_drone;
    int         height;
    int         i;

    i = 0;
    new_drone = DuplicateDrone(player, world);
    height = player->level;
    answer = NULL;
    new_drone->GoTop(new_drone, world);
    answer = asprintf("{%s", new_drone->mapTile->ListContent(new_drone->mapTile));
    if (player->level == 0) {
        answer = asprintf(" %s}", answer);
        return (answer);
    }
    while (i != height)
    {
        new_drone->GoTop(new_drone, world);
        temp = GetRessourceOnSightAtLevel(new_drone, world, i + 1);
        if (strlen(temp) > 3)
            answer = asprintf(" %s, %s", answer, temp);
        else
            answer = asprintf(" %s,", answer, temp);
        i++;
    }
    answer = asprintf("%s}", answer);
    return (answer);
}
