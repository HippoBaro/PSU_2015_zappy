/*
** Sound.h for za in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:28:38 2016 Etienne Pasteur
** Last update Mon Jun 27 00:32:54 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_SOUND_H
# define PSU_2015_ZAPPY_SOUND_H

typedef enum		e_rotation_path
  {
    CIRCULAR,
    NOCIRCULAR
  }			RotationPath;

typedef enum		e_sound_vector
  {
    STRAIGHT,
    DIAGONAL
  }			SoundVector;

typedef enum		e_sound_direction
  {
    UNCHANGED,
    GO_TOP,
    GO_RIGHT,
    GO_BOTTOM,
    GO_LEFT
  }			SoundDirection;

typedef struct		s_sound
{
  int			res_nocircular_x_absolute;
  int			res_nocircular_y_absolute;
  int			res_nocircular_x;
  int			res_nocircular_y;
  int			res_circular_x;
  int			res_circular_y;
  RotationPath	x_rotation;
  RotationPath	y_rotation;
  SoundDirection	x_direction;
  SoundDirection	y_direction;
  SoundVector		vector;
  int			X;
  int			Y;
}			Sound;

MapTile	*evaluate_sound_path(struct s_Drone *,
			     struct s_Drone *, struct s_map *);
int	GetTileNumberForDrone(MapTile *, Drone *, Map *);

#endif //PSU_2015_ZAPPY_SOUND_H
