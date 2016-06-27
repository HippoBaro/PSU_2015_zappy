/*
** MapTile.c for Zappy in /home/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 15:26:32 2016 Christian Diaconu
** Last update Mon Jun 27 02:10:18 2016 Etienne Pasteur
*/

#include "MapTile.h"
#include "Drone.h"

bool		add_refplayer(MapTile *tile, Drone *player)
{
  return (tile->drones->addElemFront(tile->drones, (void *) player));
}

bool		is_refplayer(MapTile *tile, Drone *player)
{
  t_list	*elem;

  elem = FirstPred(tile->drones, element, {
      return (bool) ((element) == (player));
    });
  if (elem != NULL)
    return (true);
  return (false);
}

bool		remove_refplayer(MapTile *tile, Drone *player)
{
  t_list	*elem;

  elem = FirstPred(tile->drones, element, {
      return (bool) ((element) == (player));
    });
  if (elem != NULL)
    return (bool) (tile->drones->removeThisElem(tile->drones,
						elem) == true);
  return (false);
}

int		count_players(MapTile *tile)
{
  return (tile->drones->countLinkedList(tile->drones));
}
