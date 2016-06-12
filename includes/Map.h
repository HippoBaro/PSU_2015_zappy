/*
** Map.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:53:51 2016 Christian Diaconu
** Last update Mon Jun 13 01:23:29 2016 Christian Diaconu
*/

#include "MapTile.h"

#ifndef _ZAPPY_MAPTILE_H_
# define _ZAPPY_MAPTILE_H_

typedef struct	s_map
{
  int		X;
  int		Y;
  t_maptile	***map;
}		t_map;


/* map_gettile() in map.c */
t_maptile       *map_gettile(t_map *world, int X, int Y);

#endif
