/*
** MapTile.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 14:48:54 2016 Christian Diaconu
** Last update Mon Jun 13 01:31:51 2016 Christian Diaconu
*/

#include <stdlib.h>
#include "Generic.h"
#include "LinkedList.h"
#include "Player.h"

/*	Map Scheme
**
**	Y <-------------|
**			|
**	0 1 2 3 4 5	|
**	X X X X X X 0	|
**	X X X X X X 1	|
**	X X X X X X 2	|
**	X X X X X X 3	|
**	X X X X X X 4	|
**	X X X X X X 5	↓
**			X
**/

#ifndef _H_ZAPPY_MAPTILE_
#define _H_ZAPPY_MAPTILE_

typedef struct		s_maptile
{
  LinkedList(Item)		*ressources;
  LinkedList(Drone)		*drones;
  int			X;
  int			Y;
}			    MapTitle;

/* init_map in maptile.c */
MapTitle       *CreateMapTitle(int X, int Y);
void		    DestroyMapTile(MapTitle *map);

#endif
