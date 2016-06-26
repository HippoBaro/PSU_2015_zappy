/*
** command.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:05:41 2016 Etienne Pasteur
** Last update Sun Jun 26 23:06:40 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		msz(char *arg, t_ecran *val)
{
  char		**tokens;
  int		i;

  i = 0;
  tokens = str_split(strdup(arg), ' ');
  if (tokens)
    {
      while (*(tokens + i))
	{
	  if (i == 0)
	    val->terrain_x = atoi(*(tokens + i));
	  else
	    val->terrain_y = atoi(*(tokens + i));
	  free(*(tokens + i));
	  i++;
        }
      free(tokens);
    }
  generate_terrain(val);
}

void		sgt(char *arg, t_ecran *val)
{
  Log(INFORMATION, "There are %s slot to connect on this server", arg);
}

void		bctIf(t_valBct *v, t_ecran *val)
{
  if (v->i == 0)
    v->x = atoi(*(v->tokens + v->i));
  if (v->i == 1)
    v->y = atoi(*(v->tokens + v->i));
  if (v->i == 2)
    val->terrain[v->x][v->y].nourriture = atoi(*(v->tokens + v->i));
  if (v->i == 3)
    val->terrain[v->x][v->y].linemate = atoi(*(v->tokens + v->i));
  if (v->i == 4)
    val->terrain[v->x][v->y].deraumere = atoi(*(v->tokens + v->i));
  if (v->i == 5)
    val->terrain[v->x][v->y].sibur = atoi(*(v->tokens + v->i));
  if (v->i == 6)
    val->terrain[v->x][v->y].mendiane = atoi(*(v->tokens + v->i));
  if (v->i == 7)
    val->terrain[v->x][v->y].phiras = atoi(*(v->tokens + v->i));
  if (v->i == 8)
    val->terrain[v->x][v->y].thystame = atoi(*(v->tokens + v->i));
}

void		bct(char *arg, t_ecran *val)
{
  t_valBct	v;

  v.x = 0;
  v.y = 0;
  v.tokens = str_split(strdup(arg), ' ');
  if (v.tokens) {
    v.i = 0;
    while (*(v.tokens + v.i)) {
      bctIf(&v, val);
      free(*(v.tokens + v.i));
      v.i++;
    }
    free(v.tokens);
  }
}
