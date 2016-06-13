/*
** map.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:15:30 2016 Christian Diaconu
** Last update Mon Jun 13 01:26:32 2016 Christian Diaconu
*/

#include "Map.h"

#define WORLD_SIZE_X    100
#define    WORLD_SIZE_Y    100
#define WORLD_POS_X    2
#define WORLD_POS_Y    3

int test_all_map() {
    MapTitle *tile;
    int passed;
    int error;
    int i_x;
    int i_y;

    Map *world;

    if ((world = CreateMap(WORLD_SIZE_X, WORLD_SIZE_Y)) == NULL) {
        printf("  ---> Creating Map %ix%i : KO\n",
               WORLD_SIZE_X, WORLD_SIZE_Y);
        return (-1);
    }
    printf("  ---> Creating map %ix%i : OK\n", WORLD_SIZE_X, WORLD_SIZE_Y);
    printf("\x1B[33m  ---> Testing all maptiles...\n");

    i_x = 0;
    error = 0;
    passed = 0;
    while (i_x != world->X) {
        i_y = 0;
        while (i_y != world->Y) {
            if ((tile = map_gettile(world, i_x, i_y)) == NULL
                && (tile->X != i_x || tile->Y == i_y)) {
                printf("\x1B[31m  ---> Getting MapTile @%ix%i : KO\n", i_x, i_y);
                error++;
                return (-1);
            }
            else {
                printf("\x1B[32m  ---> Getting MapTile @%ix%i : OK\n", i_x, i_y);
                passed++;
            }
            i_y++;
        }
        i_x++;
    }
    printf("\x1B[37m  ---> Map test execute on [%i] elements with [%i] error : ",
           passed + error, error);
    if (error > 0)
        printf("KO\n");
    else
        printf("OK\n");

    printf("\x1B[33m  ---> Destroying Map and all subsequent ressources...\n");
    world->Free(world);
}

int main() {
    test_all_map();
}
