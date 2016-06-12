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

bool		add_refplayer(t_maptile *tile, t_player *player)
{
  t_player	*this_player;

  return (tile->players->addElemFront(tile->players, (void *)this_player));
}

bool		is_refplayer(t_maptile *tile, t_player *player)
{
  t_list	*elem;
  int		i;

  i = 0;
  while ((elem = tile->players->getElementAtPos(tile->players, i)) != NULL)
    {
      if (((t_player *)elem->data) == player)
	return (true);
      i++;
    }
  return (false);
}

bool		remove_refplayer(t_maptile *tile, t_player *player)
{
  t_list	*elem;
  int		i;

  i = 0;
  while ((elem = tile->players->getElementAtPos(tile->players, i)) != NULL)
    {
      if (elem->data == player)
	return (tile->players->removeThisElem(tile->players, elem));
      i++;
    }
  return (false);
}

int		count_players(t_maptile *tile)
{
  return (tile->players->countLinkedList(tile->players));
}
