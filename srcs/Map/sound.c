/*
** sound.c for Zappy in /home/diacon_c/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 19 16:21:45 2016 Christian Diaconu
** Last update Mon Jun 27 02:05:45 2016 Etienne Pasteur
*/

#include "Map.h"
#include "Drone.h"
#include "Sound.h"
#include "MapSight.h"

MapTile		*sound_get_targed_tile(Drone *receiver, Map *world, Sound *metrics)
{
  MapTile	*tile;

  tile = receiver->mapTile;
  if (metrics->x_direction == GO_TOP)
    tile = Math_GetBottomTile(world, tile);
  else if (metrics->x_direction == GO_BOTTOM)
    tile = Math_GetTopTile(world, tile);
  if (metrics->y_direction == GO_RIGHT)
    tile = Math_GetLeftTile(world, tile);
  else if (metrics->y_direction == GO_LEFT)
    tile = Math_GetRightTile(world, tile);
  return (tile);
}

void		sound_vector_compute_1(Drone *emitter, Drone *receiver,
				       Sound *metrics, Map *world)
{
  MapTile	*temp_tile;
  int		i;

  i = 0;
  temp_tile = emitter->mapTile;
  if (emitter->mapTile->X == receiver->mapTile->X ||
      emitter->mapTile->Y == receiver->mapTile->Y)
    metrics->vector = STRAIGHT;
  else
    metrics->vector = DIAGONAL;
  while (i != metrics->X)
    {
      temp_tile = Math_GetTopTile(world, temp_tile);
      if (temp_tile->X == receiver->mapTile->X)
	{
	  metrics->x_direction = GO_TOP;
	  return ;
	}
      else
	metrics->x_direction = GO_BOTTOM;
      i++;
    }
}

void		sound_vector_compute_2(Drone *emitter, Drone *receiver,
				       Sound *metrics, Map *world)
{
  MapTile	*temp_tile;
  int		i;

  i = 0;
  temp_tile = emitter->mapTile;
  while (i != metrics->X)
    {
      temp_tile = Math_GetRightTile(world, temp_tile);
      if (temp_tile->Y == receiver->mapTile->Y)
	metrics->y_direction = GO_LEFT;
      else
	metrics->y_direction = GO_RIGHT;
      i++;
    }
}

void		sound_compile_results(Sound *metrics)
{
  if (metrics->res_nocircular_y_absolute < metrics->res_circular_y)
    {
      metrics->y_rotation = NOCIRCULAR;
      metrics->Y = metrics->res_nocircular_y_absolute;
    }
  else
    {
      metrics->y_rotation = CIRCULAR;
      metrics->Y = metrics->res_circular_y;
    }
  if (metrics->res_nocircular_x_absolute < metrics->res_circular_x)
    {
      metrics->x_rotation = NOCIRCULAR;
      metrics->X = metrics->res_nocircular_x_absolute;
    }
  else
    {
      metrics->x_rotation = CIRCULAR;
      metrics->X = metrics->res_circular_x;
    }
}

MapTile			*evaluate_sound_path(Drone *emitter,
					     Drone *receiver, Map *world)
{
  Sound			sound;

  sound.res_nocircular_x = (receiver->mapTile->X - emitter->mapTile->X);
  if (sound.res_nocircular_x < 0)
    sound.res_nocircular_x_absolute = (sound.res_nocircular_x * (-1));
  else
    sound.res_nocircular_x_absolute = (sound.res_nocircular_x);
  sound.res_nocircular_y = (receiver->mapTile->Y - emitter->mapTile->Y);
  if (sound.res_nocircular_y < 0)
    sound.res_nocircular_y_absolute = (sound.res_nocircular_y * (-1));
  else
    sound.res_nocircular_y_absolute = (sound.res_nocircular_y);
  sound.res_circular_x = (world->X - sound.res_nocircular_x);
  sound.res_circular_y = (world->Y - sound.res_nocircular_y);
  sound_compile_results(&sound);
  sound_vector_compute_1(emitter, receiver, &sound, world);
  sound_vector_compute_2(emitter, receiver, &sound, world);
  if (sound.X + sound.Y == 1 || sound.X + sound.Y == 2)
    return (emitter->mapTile);
  return (sound_get_targed_tile(receiver, world, &sound));
}
