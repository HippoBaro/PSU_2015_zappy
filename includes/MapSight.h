/*
** MapSight.h for zap in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:08:48 2016 Etienne Pasteur
** Last update Mon Jun 27 00:09:07 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_MAPSIGHT_H
# define PSU_2015_ZAPPY_MAPSIGHT_H

# include "Map.h"

MapTile	*Math_GetTopTile(Map *world, MapTile *tile);
MapTile	*Math_GetBottomTile(Map *world, MapTile *tile);
MapTile	*Math_GetLeftTile(Map *world, MapTile *tile);
MapTile	*Math_GetRightTile(Map *world, MapTile *tile);

#endif //PSU_2015_ZAPPY_MAPSIGHT_H
