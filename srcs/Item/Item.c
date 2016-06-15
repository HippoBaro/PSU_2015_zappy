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
        { THYSTAME, "thystame" }
};

static string ToString(Item *item) {
    int  	i;

    i = 0;
    while (i < 6)
    {
        if (toStringItem[i].type == item->type)
            return toStringItem[i].str;
        ++i;
    }
    Log(ERROR, "Called ToString on unknown item type.");
    exit(EXIT_FAILURE);
    return "";
}

/*static Item *FromString(string item) {
    int  	i;

    i = 0;
    while (i < 6)
    {
        if (toStringItem[i].type == item->type)
            return toStringItem[i].str;
        ++i;
    }
    Log(ERROR, "Called ToString on unknown item type.");
    exit(EXIT_FAILURE);
    return "";
}*/

void        DestroyItem(Item *item) {
    xfree(item, sizeof(Item));
}

Item        *CreateItemFrom(ItemType type) {
    Item    *ret;

    ret = xmalloc(sizeof(Item));
    ret->type = type;
    ret->ToString = &ToString;
    ret->Free = &DestroyItem;
    return ret;
}