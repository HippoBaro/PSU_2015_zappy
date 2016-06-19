/*
** drone_directions.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Wed Jun 15 15:41:09 2016 Christian Diaconu
** Last update Sun Jun 19 14:43:49 2016 Christian Diaconu
*/

#define		MAP_XY			5
#define		DRONE_START_POS_X	0
#define		DRONE_START_POS_Y	0

#include	"Map.h"
#include	"Drone.h"
#include	"Generic.h"

int		test_circual_map_move(Map *world, Drone *player, Rotation rotation)
{
  MapTile	*start;
  MapTile	*temp;
  int		i;

  /* Anoncement */
  printf("[TESTING] Moving forward with rotation set @%i°\n", rotation);


  i = 0;
  temp = NULL;
  player->Rotate(player, rotation);
  start = player->mapTile;
  temp = start;
  while (i != (MAP_XY))
    {
      player->Move(player, world);
      temp = player->mapTile;
      if (temp == NULL) {
        Log (ERROR," --> Unexpected NULL pointer arrived :(\n");
	  return (-1);
      }
      else {
	    printf(" --> Jumping to tile @[%ix%i]\n", temp->X, temp->Y);
      }
      if (start == temp)
	  {
	    Log (SUCCESS, "  --> Circular move test with drone rotation set at %i° : OK \n", rotation);
	    return (0);
	  }
      i++;
    }
  Log (ERROR,"  --> Move test with drone rotation set at %i° : KO \n", rotation);
}

int		main()
{
  Map		*world;
  Drone		*player;

  world = CreateMap(MAP_XY, MAP_XY);
  player = CreateDrone();
  world->AddDrone(world->GetTile(world, 0, 0), player);
  test_circual_map_move(world, player, TOP);
  test_circual_map_move(world, player, LEFT);
  test_circual_map_move(world, player, BOTTOM);
  test_circual_map_move(world, player, RIGHT);
  printf("Sight Works ? : %s\n", player->GetDroneSight(player, world));
}
