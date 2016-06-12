/*
** MapTile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 15:26:32 2016 Christian Diaconu
** Last update Sun Jun 12 23:09:27 2016 Christian Diaconu
*/

#include "MapTile.h"

bool		add_ressource(t_maptile *tile, ObjectType type)
{
  t_ressource	*ressource;

  if ((ressource = malloc(sizeof(t_ressource))) == NULL)
    return (false);
  ressource->type = type;
  return (tile->ressources->addElemFront(tile->ressources, (void *)ressource));
}

ObjectType	get_ressource(t_maptile *tile, ObjectType type)
{
  t_list	*elem;
  int		i;

  i = 0;
  while ((elem = tile->ressources->getElementAtPos(tile->ressources, i)) != NULL)
    {
      if (((t_ressource *)elem->data)->type == type)
	{
	  tile->ressources->removeThisElem(tile->ressources, elem);
	  return (type);
	}
      i++;
    }
  return (-1);
}

int		count_ressources(t_maptile *tile)
{
  return (tile->ressources->countLinkedList(tile->ressources));
}
