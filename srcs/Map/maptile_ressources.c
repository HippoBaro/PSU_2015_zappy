/*
** MapTile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 15:26:32 2016 Christian Diaconu
** Last update Mon Jun 13 12:54:17 2016 Christian Diaconu
*/

#include "MapTile.h"
#include "Generic.h"
#include "Item.h"

static bool        sorting_itemtype(void *elem, void *seeked_type)
{
    if (((Item *) elem)->type == (ItemType) seeked_type)
        return (true);
    return (false);
}

bool		add_ressource(MapTile *tile, ItemType type)
{
    Item        *item;

    item = CreateItemFrom(type);
    // Log(INFORMATION, "Creating a new ressource");
    return (tile->ressources->addElemFront(tile->ressources, (void *)item));
}

ItemType	get_ressource(MapTile *tile, ItemType type)
{
    t_list	    *elem;

    elem = tile->ressources->firstElementFromPredicate(tile->ressources, &sorting_itemtype, (void *) type);
    if (elem != NULL) {
        // Log(INFORMATION, "Picking up a ressource");
        tile->ressources->removeThisElem(tile->ressources, elem);
        return (type);
    }
  return (-1);
}

int		count_ressources(MapTile *tile)
{
  return (tile->ressources->countLinkedList(tile->ressources));
}
