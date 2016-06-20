//
// Created by barrauh on 6/13/16.
//

#ifndef PSU_2015_ZAPPY_ITEM_H
#define PSU_2015_ZAPPY_ITEM_H

#include "Generic.h"

struct s_item_string {
    ItemType    type;
    string      str;
};

typedef struct s_Item {
    ItemType    type;
    int         quantity;
    string      (*ToString)(struct s_Item *self);
    void        (*Free)(struct s_Item *self);
}               Item;

void        DestroyItem(Item *item);
Item        *CreateItemFrom(ItemType type);
Item        *CreateItemWithQuantity(ItemType type, int quantity);
Item        *CreateRandomItem();

#endif //PSU_2015_ZAPPY_ITEM_H
