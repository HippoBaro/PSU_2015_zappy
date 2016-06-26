/*
** terrain.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:09:59 2016 Etienne Pasteur
** Last update Sun Jun 26 23:12:03 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		draw_terrain_next(t_ecran *val, int i, int j,
				  void (*funcPtr[7])(SDL_Rect, t_ecran *, int, int))
{
  SDL_Rect	position;
  int		k;

  if ((i + val->x) < val->terrain_x &&
      (j + val->y) < val->terrain_y)
    {
      val->display = (val->terrain[i + val->x][j + val->y].texture ==
		      0)
	? val->dirt : val->grass;
      position.x = i * 100;
      position.y = j * 100;
      SDL_BlitSurface(val->display, NULL, val->ecran, &position);
      k = -1;
      while (++k < 7)
	funcPtr[k](position, val, i, j);
    }
}

void		draw_terrain(t_ecran *val)
{
  void		(*funcPtr[7])(SDL_Rect, t_ecran *, int, int);
  int		i;
  int		j;

  funcPtr[0] = blitNourriture;
  funcPtr[1] = blitLinemate;
  funcPtr[2] = blitDeraumere;
  funcPtr[3] = blitSibur;
  funcPtr[4] = blitMendiane;
  funcPtr[5] = blitPhiras;
  funcPtr[6] = blitThystame;

  i = -1;
  while (++i < 10)
    {
      j = -1;
      while (++j < 10)
	draw_terrain_next(val, i, j, funcPtr);
    }
  SDL_Flip(val->ecran);
}

void		fill_randPosGraph(t_ecran *val, int i, int j)
{
  val->terrain[i][j].texture = (rand() % 2);
  val->terrain[i][j].position_nourriture.x = rand() % 80;
  val->terrain[i][j].position_nourriture.y = rand() % 80;
  val->terrain[i][j].position_linemate.x = rand() % 80;
  val->terrain[i][j].position_linemate.y = rand() % 80;
  val->terrain[i][j].position_deraumere.x = rand() % 80;
  val->terrain[i][j].position_deraumere.y = rand() % 80;
  val->terrain[i][j].position_sibur.x = rand() % 80;
  val->terrain[i][j].position_sibur.y = rand() % 80;
  val->terrain[i][j].position_mendiane.x = rand() % 80;
  val->terrain[i][j].position_mendiane.y = rand() % 80;
  val->terrain[i][j].position_phiras.x = rand() % 80;
  val->terrain[i][j].position_phiras.y = rand() % 80;
  val->terrain[i][j].position_thystame.x = rand() % 80;
  val->terrain[i][j].position_thystame.y = rand() % 80;
}

void		generate_terrain(t_ecran *val)
{
  int		i;
  int		j;

  i = -1;
  val->terrain = malloc(sizeof(t_tile *) * val->terrain_x);
  while (++i < val->terrain_x)
    {
      val->terrain[i] = malloc(sizeof(t_tile) * val->terrain_y);
      j = -1;
      while (++j < val->terrain_y)
	fill_randPosGraph(val, i, j);
    }
}

void		free_terrain(t_ecran *val)
{
  int		i;

  i = -1;
  while (++i < val->terrain_x)
    free(val->terrain[i]);
  free(val->terrain);
}
