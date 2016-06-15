/*
** MapTile.h for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 14:48:54 2016 Christian Diaconu
** Last update Tue Jun 14 14:45:12 2016 Christian Diaconu
*/

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

#include "LinkedList.h"
#include "Drone.h"

typedef struct	    s_map Map;

typedef struct		s_maptile
{
    Map             *map;
    LinkedList(Item)	*ressources;
    LinkedList(Drone) *drones;
    int			    X;
    int			    Y;

    /* FX Ptr - Game Logic */
    struct s_maptile         *(*GetTopTile)(Drone *drone, struct s_map *map);
    struct s_maptile         *(*GetBottomTile)(Drone*drone, struct s_map *map);
    struct s_maptile         *(*GetLeftTile)(Drone *drone, struct s_map *map);
    struct s_maptile         *(*GetRightTile)(Drone *drone, struct s_map *map);


    /* FX Ptr - Players */
    bool		    (*AddDrone)(struct s_maptile *tile, Drone *drone);
    bool            (*DroneExist)(struct s_maptile *tile, Drone *drone);
    bool		    (*RemoveDrone)(struct s_maptile *tile, Drone *drone);
    int		        (*CountDrones)(struct s_maptile *tile);

    /* FX Ptr - Ressources */
    bool		    (*AddRessource)(struct s_maptile *tile, Item *item);
    ItemType	    (*GetRessource)(struct s_maptile *tile, ItemType type);
    int		        (*CountRessources)(struct s_maptile *tile);
    struct s_maptile *(*SeedLoot)( struct s_maptile *self);
    string		    (*ListContent)(struct s_maptile *tile);

    /* FX Ptr - Generic */
    void            (*Free)(struct s_maptile *tile);
}			        MapTile;

/* init_map in maptile.c */
MapTile       *CreateMapTile(int X, int Y);
void        DestroyMapTile(MapTile *mapTile);

/* FX Ptr - Players */
bool		add_refplayer(struct s_maptile *tile, Drone *player);
bool        is_refplayer(struct s_maptile *tile, Drone *player);
bool		remove_refplayer(struct s_maptile *tile, Drone *player);
int		    count_players(struct s_maptile *tile);

/* FX Ptr - Ressources */
bool		add_ressource(MapTile *tile, Item *item);
ItemType	get_ressource(struct s_maptile *tile, ItemType type);
int		    count_ressources(struct s_maptile *tile);
void		free_maptile(struct s_maptile *map);

/* FX Ptr - Tile Geographics tools */
struct s_maptile         *GetTopTile(Drone *drone, struct s_map *map);
struct s_maptile         *GetBottomTile(Drone *drone, struct s_map *map);
struct s_maptile         *GetLeftTile(Drone *drone, struct s_map *map);
struct s_maptile         *GetRightTile(Drone *drone, struct s_map *map);

#endif
