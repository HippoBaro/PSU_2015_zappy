/*
** utils.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:12:12 2016 Etienne Pasteur
** Last update Sun Jun 26 23:24:00 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		splitVarInit(t_splitVar *v, char *a_str, const char a_delim)
{
  char	*tmp;

  tmp = a_str;
  v->result = 0;
  v->count = 0;
  v->last_comma = 0;
  v->delim[0] = a_delim;
  v->delim[1] = 0;
  while (*tmp)
    {
      if (a_delim == *tmp)
	{
	  v->count++;
	  v->last_comma = tmp;
        }
      tmp++;
    }
}

char		**str_split(char *a_str, const char a_delim)
{
  t_splitVar	v;

  splitVarInit(&v, a_str, a_delim);
  v.count += v.last_comma < (a_str + strlen(a_str) - 1);
  v.count++;
  v.result = malloc(sizeof(char *) * v.count);
  if (v.result) {
    v.idx = 0;
    v.token = strtok(a_str, v.delim);
    while (v.token) {
      assert(v.idx < v.count);
      *(v.result + v.idx++) = strdup(v.token);
      v.token = strtok(0, v.delim);
    }
    *(v.result + v.idx) = 0;
  }
  free(a_str);
  return (v.result);
}
