/*
** sound_main.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Mon Jun 20 21:49:34 2016 Christian Diaconu
** Last update Sat Jun 25 12:32:52 2016 Christian Diaconu
*/

#define MAP_XY				    10
#define DRONE1_START_POS_X		5
#define DRONE1_START_POS_Y		5
#define DRONE2_START_POS_X		9
#define DRONE2_START_POS_Y		0

#include "Map.h"
#include "Drone.h"
#include "Team.h"
#include "Sound.h"
#include "Generic.h"

int		main()
{
  Map		*world;
  Drone		*emitter;
  Drone		*receiver;
  Team		*team;
  MapTile	*tile;

  world = CreateMap(NULL, MAP_XY, MAP_XY);
  team = CreateTeamFrom("hello", 5);
  emitter = CreateDrone(team);
  receiver = CreateDrone(team);
  world->AddDrone(world->GetTile(world, DRONE1_START_POS_X, DRONE1_START_POS_Y), emitter);
  world->AddDrone(world->GetTile(world, DRONE2_START_POS_X, DRONE2_START_POS_Y), receiver);
  printf("[DRONE 1] X@%i && Y@%i\n", DRONE1_START_POS_X, DRONE1_START_POS_Y);
  printf("[DRONE 2] X@%i && Y@%i\n", DRONE2_START_POS_X, DRONE2_START_POS_Y);
  tile = world->GetTileReceivingSound(emitter, receiver, world);
  printf("Sound will be recieved form the tile positioned at X: [%i] && Y: [%i]\n", tile->X, tile->Y);
  printf("%s\n", emitter->GetDroneSight(emitter, world));
}
