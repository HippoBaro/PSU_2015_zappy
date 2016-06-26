/*
** MapTile.h for Zappy in /home/diacon_c/PSU_2015_zappy/includes
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 14:48:54 2016 Christian Diaconu
** Last update Mon Jun 27 00:45:29 2016 Etienne Pasteur
*/

#ifndef _H_ZAPPY_MAPTILE_
# define _H_ZAPPY_MAPTILE_

# include "LinkedList.h"
# include "Item.h"

typedef struct	s_map Map;
typedef struct	s_Drone Drone;

typedef struct		s_tempfind
{
  string		ressources;
  string		drones;
  string		ret;
  bool			isFirst;
}			TempFind;

typedef struct		s_maptile
{
  Map			*map;
  LinkedList(Item)	*ressources;
  LinkedList(Drone)	*drones;
  int			X;
  int			Y;

  struct s_maptile	*(*GetTopTile)(Drone *drone, struct s_map *map);
  struct s_maptile	*(*GetBottomTile)(Drone*drone, struct s_map *map);
  struct s_maptile	*(*GetLeftTile)(Drone *drone, struct s_map *map);
  struct s_maptile	*(*GetRightTile)(Drone *drone, struct s_map *map);
  bool			(*AddDrone)(struct s_maptile *tile, Drone *drone);
  bool			(*DroneExist)(struct s_maptile *tile, Drone *drone);
  bool			(*RemoveDrone)(struct s_maptile *tile, Drone *drone);
  int			(*CountDrones)(struct s_maptile *tile);
  bool			(*AddRessource)(struct s_maptile *tile, Item *item);
  Item			*(*GetRessource)(struct s_maptile *tile, ItemType type);
  int			(*CountRessources)(struct s_maptile *tile);
  int			(*CountRessource)(struct s_maptile *tile, ItemType type);
  struct s_maptile	*(*SeedLoot)(struct s_maptile *self);
  string		(*ListContent)(struct s_maptile *tile);
  void			(*Free)(struct s_maptile *tile);
}			MapTile;

MapTile			*CreateMapTile(Map *map, int X, int Y);
void			DestroyMapTile(MapTile *mapTile);
bool			add_refplayer(struct s_maptile *tile, Drone *player);
bool			is_refplayer(struct s_maptile *tile, Drone *player);
bool			remove_refplayer(struct s_maptile *tile, Drone *player);
int			count_players(struct s_maptile *tile);
bool			add_ressource(MapTile *tile, Item *item);
Item			*get_ressource(MapTile *tile, ItemType type);
int			count_ressources(struct s_maptile *tile);
int			countRessource(MapTile *tile, ItemType type);
void			free_maptile(struct s_maptile *map);
struct s_maptile	*GetTopTile(Drone *drone, struct s_map *map);
struct s_maptile	*GetBottomTile(Drone *drone, struct s_map *map);
struct s_maptile	*GetLeftTile(Drone *drone, struct s_map *map);
struct s_maptile	*GetRightTile(Drone *drone, struct s_map *map);

#endif
