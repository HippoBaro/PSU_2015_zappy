/*
** Generic.c for zapppy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Generic
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:54:43 2016 Etienne Pasteur
** Last update Mon Jun 27 01:58:12 2016 Etienne Pasteur
*/

#include "Generic.h"

uint64_t	on_heap = 0;

void		*xmalloc(size_t size)
{
  void		*ret;

  if ((ret = malloc(size)) == NULL)
    {
      Log(ERROR, (string const) "Failed to allocate memory. Abording.");
      exit(EXIT_FAILURE);
    }
  on_heap += size;
  return (ret);
}

void		*xcalloc(size_t nelem, size_t elsize)
{
  void		*ret;

  ret = xmalloc (nelem * elsize);
  bzero (ret, nelem * elsize);
  return (ret);
}

void		xfree(void *ptr, size_t size)
{
  if (ptr == NULL)
    return;
  on_heap -= size;
  free(ptr);
}

int		asymetricRandMinMax(int rolls, int min, int max)
{
  int		i;
  int		tmp;
  int		ret;

  i = -1;
  tmp = max;
  ret = max;
  while (++i < rolls)
    {
      tmp = randMinMax(min, max);
      ret = tmp < ret ? tmp : ret;
    }
  return (ret);
}
