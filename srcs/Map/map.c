/*
** map.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 23:17:28 2016 Christian Diaconu
** Last update Mon Jun 13 00:25:34 2016 Christian Diaconu
*/

#include "Map.h"

t_map		*createmap(int X, int Y)
{
  t_map		*world;
  int		i_x;
  int		i_y;

  i_x = 0;
  if ((world = malloc(sizeof(t_map))) == NULL)
    return (NULL);
  world->X = X;
  world->Y = Y;
  if ((world->map = malloc(sizeof(t_maptile *) * X)) == NULL)
    return (NULL);
  while (i_x != X)
    {
      if ((world->map[i_x] = malloc(sizeof(t_maptile *) * Y)) == NULL)
	return (NULL);
      i_y = 0;
      while (i_y != Y)
	{
	  world->map[i_x][i_y] = init_maptile(i_x, i_y);
	  i_y++;
	}
      i_x++;
    }
  return (world);
}

t_maptile	*map_gettile(t_map *world, int X, int Y)
{
  if (world == NULL)
    return (NULL);
  if (X > world->X || Y > world->Y)
    return (NULL);
  return (world->map[X][Y]);
}
