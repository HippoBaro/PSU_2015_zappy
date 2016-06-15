//
// Created by diacon_c on 15/06/16.
//

#ifndef PSU_2015_ZAPPY_MAPSIGHT_H
#define PSU_2015_ZAPPY_MAPSIGHT_H

#include "Map.h"

/* CAUTION !
**
** Those functions do not take in consideration the actual rotation of the player.
** There all based on the map it-self :
**
**				 TOP
**	LEFT		  X			RIGHT
**				BOTTOM
**
** --> [ONLY PURE MATHS]
*/

MapTile            *Math_GetTopTile(Map *world, MapTile *tile);
MapTile            *Math_GetBottomTile(Map *world, MapTile *tile);
MapTile            *Math_GetLeftTile(Map *world, MapTile *tile);
MapTile            *Math_GetRightTile(Map *world, MapTile *tile);

#endif //PSU_2015_ZAPPY_MAPSIGHT_H
