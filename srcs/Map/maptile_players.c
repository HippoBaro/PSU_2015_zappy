/*
** MapTile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 15:26:32 2016 Christian Diaconu
** Last update Sun Jun 12 23:04:09 2016 Christian Diaconu
*/

#include "MapTile.h"
#include "Drone.h"

static bool        sorting_player(void *elem, void *player)
{
  if ((elem) == (player))
    return (true);
  return (false);
}

bool		  add_refplayer(t_maptile *tile, Drone *player)
{
  return (tile->players->addElemFront(tile->players, (void *)player));
}

bool		  is_refplayer(t_maptile *tile, Drone *player)
{
  t_list	    *elem;

  elem = tile->players->firstElementFromPredicate(tile->players, &sorting_player, (void *) player);
  if (elem != NULL) {
    return (true);
  }
  return (false);
}

bool		  remove_refplayer(t_maptile *tile, Drone *player)
{
  t_list	    *elem;

  elem = tile->players->firstElementFromPredicate(tile->players, &sorting_player, (void *) player);
  if (elem != NULL) {
    return (tile->players->removeThisElem(tile->players, elem) == true);
  }
  return (false);
}

int		    count_players(t_maptile *tile)
{
  return (tile->players->countLinkedList(tile->players));
}
