/*
** Inventory.c for  in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 13:47:27 2016 Etienne Pasteur
** Last update Sun Jun 26 15:03:21 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*ListInventory(struct s_Drone *self, Request *request)
{
  string	rt;
  bool		isFirst;

  rt = NULL;
  isFirst = true;
  if (self->inventory->countLinkedList(self->inventory) > 0)
      ForEach(self->inventory, param, {
					 Item *item = (Item *) param;
					 if (!isFirst)
					   rt = strappend(rt, ", ", FIRST);
					 rt = strappend(rt, item->ToString(item), FIRST);
					 rt = strappend(rt, asprintf(" %d", item->quantity), BOTH);
					 isFirst = false;
				       });
  rt = strappend(rt, "}", FIRST);
  rt = strappend("{", rt, SECOND);
  return (CreateResponseFromFdWithMessage(self->socketFd, rt));
}

Response	*Take(struct s_Drone *self, Request *request)
{
  Item		*item;
  t_list	*elem;

  item = self->mapTile->GetRessource(self->mapTile,
				     ItemFromString(request->actionSubject));
  if (item == NULL)
    return CreateKoResponseFrom(request);
  elem = FirstPred(self->inventory, itemPred, {
							return (bool)(((Item *)itemPred)->type ==
								      ItemFromString(request->actionSubject));
						      });
  if (elem != NULL && elem->data != NULL)
    ((Item *)elem->data)->quantity++;
  else
    self->inventory->addElemFront(self->inventory, CreateItemFrom(item->type));
  item->Free(item);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

Response	*Drop (struct s_Drone *self, Request *request)
{
  self->DropInternal(self, ItemFromString(request->actionSubject), 1, false);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

void		DropInternal(struct s_Drone *self, ItemType itemType,
			     int quantity, bool destroyItem)
{
  t_list	*elem;

  elem = FirstPred(self->inventory, itemPred, {
							return (bool)(((Item *)itemPred)->type == itemType);
						      });
  if (elem != NULL && elem->data != NULL && quantity > 0)
    {
      if (((Item *)elem->data)->quantity == 1)
	{
	  self->inventory->removeThisElem(self->inventory, elem);
	  if (!destroyItem)
	    self->mapTile->AddRessource(self->mapTile, elem->data);
	  else
	    self->inventory->freeThisElem(self->inventory,
					  (void (*)(void *)) &DestroyItem, elem);
	}
      else
	{
	  ((Item *) elem->data)->quantity--;
	  if (!destroyItem)
	    self->mapTile->AddRessource(self->mapTile,
					CreateItemFrom(((Item *) elem->data)->type));
	  self->DropInternal(self, itemType, --quantity, destroyItem);
	}
    }
}
