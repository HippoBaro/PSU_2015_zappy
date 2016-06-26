/*
** Item.h for ez in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:52:00 2016 Etienne Pasteur
** Last update Sun Jun 26 23:58:57 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_ITEM_H
# define PSU_2015_ZAPPY_ITEM_H

# include "Generic.h"

struct		s_item_string
{
  ItemType	type;
  string	str;
};

typedef struct	s_Item
{
  ItemType	type;
  int		quantity;
  string	(*ToString)(struct s_Item *self);
  void		(*Free)(struct s_Item *self);
}		Item;

void		DestroyItem(Item *item);
Item		*CreateItemFrom(ItemType type);
Item		*CreateItemWithQuantity(ItemType type, int quantity);
Item		*CreateRandomItem();
ItemType	ItemFromString(string item);

static const struct s_item_string toStringItem[] =
  {
    { LINEMATE, "linemate" },
    { DERAUMERE, "deraumere" },
    { SIBUR, "sibur" },
    { MENDIANE, "mendiane" },
    { PHIRAS, "phiras" },
    { THYSTAME, "thystame" },
    { NOURRITURE, "nourriture" }
  };

#endif //PSU_2015_ZAPPY_ITEM_H
