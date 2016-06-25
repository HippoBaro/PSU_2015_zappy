//
// Created by diacon_c on 25/06/16.
//

#include "Map.h"
#include "Drone.h"
#include "Sound.h"
#include "MapSight.h"

int     evaluate_sound_path_numeric(Drone *emitter, Drone *receiver, Map *world)
{
  Sound sound;

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
  //sound_compile_results(&sound);
  //sound_vector_compute_1(emitter, receiver, &sound, world);
  //sound_vector_compute_2(emitter, receiver, &sound, world);
  return (-1);
}
