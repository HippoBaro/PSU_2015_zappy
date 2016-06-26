/*
** blitRess.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:02:24 2016 Etienne Pasteur
** Last update Sun Jun 26 23:02:26 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		blitNourriture(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x +
    val->terrain[i + val->x][j + val->y].position_nourriture.x;
  p.y = position.y +
    val->terrain[i + val->x][j + val->y].position_nourriture.y;
  if (val->terrain[i + val->x][j + val->y].nourriture != 0)
    SDL_BlitSurface(val->nourriture, NULL, val->ecran, &p);
}

void		blitLinemate(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x +
    val->terrain[i + val->x][j + val->y].position_linemate.x;
  p.y = position.y +
    val->terrain[i + val->x][j + val->y].position_linemate.y;
  if (val->terrain[i + val->x][j + val->y].linemate != 0)
    SDL_BlitSurface(val->linemate, NULL, val->ecran, &p);
}

void		blitDeraumere(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x +
    val->terrain[i + val->x][j + val->y].position_deraumere.x;
  p.y = position.y +
    val->terrain[i + val->x][j + val->y].position_deraumere.y;
  if (val->terrain[i + val->x][j + val->y].deraumere != 0)
    SDL_BlitSurface(val->deraumere, NULL, val->ecran, &p);
}

void		blitSibur(SDL_Rect position, t_ecran *val, int i, int j)
{
  SDL_Rect	p;

  p.x = position.x + val->terrain[i + val->x][j + val->y].position_sibur.x;
  p.y = position.y + val->terrain[i + val->x][j + val->y].position_sibur.y;
  if (val->terrain[i + val->x][j + val->y].sibur != 0)
    SDL_BlitSurface(val->sibur, NULL, val->ecran, &p);
}
