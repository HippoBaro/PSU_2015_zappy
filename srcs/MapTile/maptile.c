/*
** maptile.c for Zappy in /home/diacon_c/Documents/repository/PSU_2015_zappy
**
** Made by Christian Diaconu
** Login   <diacon_c@epitech.net>
**
** Started on  Sun Jun 12 19:14:56 2016 Christian Diaconu
** Last update Sun Jun 26 23:15:20 2016 Christian Diaconu
*/

#include <Map.h>
#include <Drone.h>

void		DestroyMapTile(MapTile *mapTile)
{
  mapTile->drones->freeAll(mapTile->drones,
			   (void (*)(void *)) &DestroyDrone);
  mapTile->drones->Free(mapTile->drones);
  mapTile->ressources->freeAll(mapTile->ressources,
			       (void (*)(void *)) &DestroyItem);
  mapTile->ressources->Free(mapTile->ressources);
  xfree(mapTile, sizeof(MapTile));
}

static MapTile	*SeedLoot(MapTile *self)
{
  int		i;
  int		loot;

  loot = asymetricRandMinMax(5, 1, 10);
  i = 0;
  while (i < loot)
    {
      self->AddRessource(self, CreateRandomItem());
      ++i;
    }
  return (self);
}

static void	ListContent2(MapTile *self, TempFind *find)
{
  Item		*item;

  if (self->ressources->countLinkedList(self->ressources) > 0)
    ForEach(self->ressources, param, {
	item = (Item *) param;
	if (!find->isFirst)
	  find->ressources = strappend(find->ressources, " ", FIRST);
	find->ressources = strappend(find->ressources, item->ToString(item), FIRST);
	find->isFirst = false;
      });
  find->isFirst = true;
  if (self->drones->countLinkedList(self->drones) > 0)
    ForEach(self->drones, param, {
        if (!find->isFirst)
	  find->drones = strappend(find->drones, " ", FIRST);
	find->drones = strappend(find->drones, "player", FIRST);
	find->isFirst = false;
      });
}

static string	ListContent(MapTile *self)
{
  TempFind	find;

  find.ressources = NULL;
  find.drones = NULL;
  find.ret = NULL;
  find.isFirst = true;
  ListContent2(self, &find);
  if (find.ressources == NULL && find.drones == NULL)
    return strdup("");
  else if (find.ressources == NULL && find.drones != NULL) {
    find.ret = asprintf("%s", find.drones);
    xfree(find.drones, strlen(find.drones));
  }
  else if (find.ressources != NULL && find.drones == NULL) {
    find.ret = asprintf("%s", find.ressources);
    xfree(find.ressources, strlen(find.ressources));
  }
  else if (find.ressources != NULL && find.drones != NULL) {
    find.ret = asprintf("%s %s", find.ressources, find.drones);
    xfree(find.ressources, strlen(find.ressources));
    xfree(find.drones, strlen(find.drones));
  }
  return find.ret;
}

MapTile		*CreateMapTile(Map *map, int X, int Y)
{
  MapTile	*tile;

  tile = xmalloc(sizeof(MapTile));
  tile->X = X;
  tile->Y = Y;
  tile->map = map;
  tile->drones = CreateLinkedList();
  tile->ressources = CreateLinkedList();
  tile->AddDrone = &add_refplayer;
  tile->CountDrones = &count_players;
  tile->CountRessources = &count_ressources;
  tile->CountRessource = &countRessource;
  tile->AddRessource = &add_ressource;
  tile->GetRessource = &get_ressource;
  tile->DroneExist = &is_refplayer;
  tile->RemoveDrone = &remove_refplayer;
  tile->GetTopTile = &GetTopTile;
  tile->GetBottomTile = &GetBottomTile;
  tile->GetLeftTile = &GetLeftTile;
  tile->GetRightTile = &GetRightTile;
  tile->SeedLoot = &SeedLoot;
  tile->ListContent = &ListContent;
  tile->Free = &DestroyMapTile;
  return (tile);
}
