/*
** MapTile.c for Zappy in /PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 15:26:32 2016 Christian Diaconu
** Last update Mon Jun 27 02:11:26 2016 Etienne Pasteur
*/

#include "MapTile.h"
#include "Generic.h"
#include "Item.h"

static bool		sorting_itemtype(void *elem, void *seeked_type)
{
  if (((Item *) elem)->type == (ItemType) seeked_type)
    return (true);
  return (false);
}

bool			add_ressource(MapTile *tile, Item *item)
{
  return (tile->ressources->addElemFront(tile->ressources, (void *)item));
}

Item			*get_ressource(MapTile *tile, ItemType type)
{
  t_list		*elem;
  Item			*ret;

  elem = tile->ressources->firstElementFromPredicate(tile->ressources,
						     &sorting_itemtype, (void *) type);
  if (elem != NULL && elem->data != NULL)
    {
      ret = elem->data;
      tile->ressources->removeThisElem(tile->ressources, elem);
      return (ret);
    }
  return (NULL);
}

int			count_ressources(MapTile *tile)
{
  return (tile->ressources->countLinkedList(tile->ressources));
}

int			countRessource(MapTile *tile, ItemType type)
{
  int			ret;

  ret = 0;
  ForEach(tile->ressources, res, {
      if (((Item *)res)->type == type)
	res += ((Item *)res)->quantity;
    });
  return (ret);
}
