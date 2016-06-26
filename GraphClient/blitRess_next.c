/*
** blitRess_next.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:02:44 2016 Etienne Pasteur
** Last update Sun Jun 26 23:02:49 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		blitMendiane(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x +
    val->terrain[i + val->x][j + val->y].position_mendiane.x;
  p.y = position.y +
    val->terrain[i + val->x][j + val->y].position_mendiane.y;
  if (val->terrain[i + val->x][j + val->y].mendiane != 0)
    SDL_BlitSurface(val->mendiane, NULL, val->ecran, &p);
}

void		blitPhiras(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x + val->terrain[i + val->x][j + val->y].position_phiras.x;
  p.y = position.y + val->terrain[i + val->x][j + val->y].position_phiras.y;
  if (val->terrain[i + val->x][j + val->y].phiras != 0)
    SDL_BlitSurface(val->phiras, NULL, val->ecran, &p);
}

void		blitThystame(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x +
    val->terrain[i + val->x][j + val->y].position_thystame.x;
  p.y = position.y +
    val->terrain[i + val->x][j + val->y].position_thystame.y;
  if (val->terrain[i + val->x][j + val->y].thystame != 0)
    SDL_BlitSurface(val->thystame, NULL, val->ecran, &p);
}
