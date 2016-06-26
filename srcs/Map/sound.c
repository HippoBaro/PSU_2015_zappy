/*
** sound.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/unit-tests
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 19 16:21:45 2016 Christian Diaconu
** Last update Mon Jun 20 21:52:36 2016 Christian Diaconu
*/

#include "Map.h"
#include "Drone.h"
#include "Sound.h"
#include "MapSight.h"

/*
 * This function might be a bit confusing, illustrated by an example :) !
 * Why when 'metrics->x_direction == GO_TOP' will result in 'tile = Math_GetBottomTile(world, tile);' ?
 * Easy, the sound vector direction for a given axel is compute form the emitter to the receiver.
 * This means, and only because the map is circular, that if the sound goes up it will be received by
 * the other drone at it's bottom. (and only if there are not at the same level [x])
 */
MapTile		*sound_get_targed_tile(Drone *receiver, Map *world, Sound *metrics)
{
  MapTile		*tile;

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

/*
 * Calculating the vector direction, globally and on the X and Y axel with the,
 * sound_vector_compute_1 && sound_vector_compute_2 functions
 */

void		sound_vector_compute_1(Drone *emitter, Drone *receiver, Sound *metrics, Map *world)
{
  MapTile		*temp_tile;
  int			i;

  // Compute target angle
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

/*
 * Calculating the vector direction, globally and on the X and Y axel with the,
 * sound_vector_compute_1 && sound_vector_compute_2 functions
 */
void		sound_vector_compute_2(Drone *emitter, Drone *receiver, Sound *metrics, Map *world)
{
  MapTile		*temp_tile;
  int			i;

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

/*
 * This functions compiles all the calculated metrics in order to get compelling results.
 */
void		sound_compile_results(Sound *metrics)
{
  // Setting'up best path for axe Y !
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
  // Setting'up best path for axe X !
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

MapTile	    *evaluate_sound_path(Drone *emitter, Drone *receiver, Map *world)
{
  Sound			sound;

  // Evaluating distance between the two drone on X's axe not in no circual way.
  sound.res_nocircular_x = (receiver->mapTile->X - emitter->mapTile->X);
  if (sound.res_nocircular_x < 0)
    sound.res_nocircular_x_absolute = (sound.res_nocircular_x * (-1));
  else
    sound.res_nocircular_x_absolute = (sound.res_nocircular_x);

  // Evaluating distance between the two drone on Y's axe not in no circual way.
  sound.res_nocircular_y = (receiver->mapTile->Y - emitter->mapTile->Y);
  if (sound.res_nocircular_y < 0)
    sound.res_nocircular_y_absolute = (sound.res_nocircular_y * (-1));
  else
    sound.res_nocircular_y_absolute = (sound.res_nocircular_y);

  // Evaluating distance between the two drone on X's axe in circual way.
  sound.res_circular_x = (world->X - sound.res_nocircular_x);
  // Evaluating distance between the two drone on Y's axe in circual way.
  sound.res_circular_y = (world->Y - sound.res_nocircular_y);

  // Compilling results
  sound_compile_results(&sound);
  sound_vector_compute_1(emitter, receiver, &sound, world);
  sound_vector_compute_2(emitter, receiver, &sound, world);


  printf("[Drone 1] X@%i || Y@%i\n", emitter->mapTile->X, emitter->mapTile->Y);
  printf("[Drone 2] X@%i || Y@%i\n", receiver->mapTile->X, receiver->mapTile->Y);
  printf("[AXE -> X]  --> No Circular mode will take [%i] steps && Circular mode will take [%i] steps\n", sound.res_nocircular_x, sound.res_circular_x);
  printf("[AXE -> Y]  --> No Circular mode will take [%i] steps && Circular mode will take [%i] steps\n", sound.res_nocircular_y, sound.res_circular_y);
  printf("[BEST PATH] : X:%i || Y:%i\n", sound.X, sound.Y);

  if (sound.vector == STRAIGHT)
    printf(" ---> Vector direction is [STRAIGHT]\n");
  if (sound.vector == DIAGONAL)
    printf(" ---> Vector direction is in [DIAGONAL]\n");

  if (sound.x_direction == GO_TOP)
    printf(" ---> [X] path finding conclude going TOP\n");
  if (sound.x_direction == GO_RIGHT)
    printf(" ---> [X] path finding conclude going RIGHT\n");
  if (sound.x_direction == GO_BOTTOM)
    printf(" ---> [X] path finding conclude going BOTTOM\n");
  if (sound.x_direction == GO_LEFT)
    printf(" ---> [X] path finding conclude going  LEFT\n");

  if (sound.y_direction == GO_TOP)
    printf(" ---> [Y] path finding conclude going TOP\n");
  if (sound.y_direction == GO_RIGHT)
    printf(" ---> [Y] path finding conclude going RIGHT\n");
  if (sound.y_direction == GO_BOTTOM)
    printf(" ---> [Y] path finding conclude going BOTTOM\n");
  if (sound.y_direction == GO_LEFT)
    printf(" ---> [Y] path finding conclude going LEFT\n");

  if (sound.X + sound.Y == 1 || sound.X + sound.Y == 2)
    return (emitter->mapTile);
  return (sound_get_targed_tile(receiver, world, &sound));
}
