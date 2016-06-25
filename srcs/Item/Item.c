//
// Created by barrauh on 6/13/16.
//

#include "Item.h"

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

static string ToString(Item *item) {
    int  	i;

    i = 0;
    while (i < 7)
    {
        if (toStringItem[i].type == item->type)
            return toStringItem[i].str;
        ++i;
    }
    Log(ERROR, "Called ToString on unknown item type.");
    return "";
}

ItemType ItemFromString(string item) {
    int  	i;

    i = 0;
    if (item == NULL)
        Log(ERROR, "Called FromString with NULL string.");
    while (i < 7)
    {
        if (strcmp(toStringItem[i].str, item) == 0)
            return toStringItem[i].type;
        ++i;
    }
    return UNKNOWN_ITEMTYPE;
}

void        DestroyItem(Item *item) {
    xfree(item, sizeof(Item));
}

Item        *CreateRandomItem() {
    return CreateItemFrom((ItemType) randMinMax(0, 6));
}

Item        *CreateItemWithQuantity(ItemType type, int quantity) {
    Item *ret;

    ret = CreateItemFrom(type);
    ret->quantity = quantity;
    return ret;
}

Item        *CreateItemFrom(ItemType type) {
    Item    *ret;

    ret = xmalloc(sizeof(Item));
    ret->type = type;
    ret->quantity = 1;
    ret->ToString = &ToString;
    ret->Free = &DestroyItem;
    return ret;
}