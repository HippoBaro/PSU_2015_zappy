//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *ListInventory(struct s_Drone *self, Request *request) {
    //todo refactor to tak into account quantity
    string ret = NULL;
    bool isFirst;

    isFirst = true;
    if (self->inventory->countLinkedList(self->inventory) > 0)
        self->inventory->forEachElements(self->inventory, lambda(void, (void *param, void *t), {
            Item *item = (Item *)param;
            if (!isFirst)
                ret = strappend(ret, ", ", FIRST);
            ret = strappend(ret, item->ToString(item), FIRST);
            isFirst = false;
        }), NULL);
    ret = strappend(ret, "}", FIRST);
    ret = strappend("{", ret, SECOND);
    return CreateResponseFromFdWithMessage(self->socketFd, ret);
}

Response *Take (struct s_Drone *self, Request *request) {
    Item *item;
    t_list *elem;

    item = self->mapTile->GetRessource(self->mapTile, ItemFromString(request->actionSubject));
    if (item == NULL)
        return CreateResponseFromFdWithMessage(self->socketFd, strdup("ko"));
    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == ItemFromString(request->actionSubject));
    }), NULL);
    if (elem != NULL && elem->data != NULL)
    {
        ((Item *)elem->data)->quantity++;
        item->Free(item);
    }
    else
        self->inventory->addElemFront(self->inventory, CreateItemFrom(item->type));
    item->Free(item);
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

Response *Drop (struct s_Drone *self, Request *request) {
    self->DropInternal(self, ItemFromString(request->actionSubject), 1, false);
    return CreateResponseFromFdWithMessage(self->socketFd, strdup("ok"));
}

void DropInternal(struct s_Drone *self, ItemType itemType, int quantity, bool destroyItem) {
    t_list *elem;

    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == itemType);
    }), NULL);
    if (elem != NULL && elem->data != NULL) {
        if (((Item *)elem->data)->quantity == 1)
        {
            self->inventory->removeThisElem(self->inventory, elem);
            if (!destroyItem)
                self->mapTile->AddRessource(self->mapTile, elem->data);
            else
                self->inventory->freeThisElem(self->inventory, (void (*)(void *)) &DestroyItem, elem);
        }
        else {
            ((Item *) elem->data)->quantity--;
            if (!destroyItem)
                self->mapTile->AddRessource(self->mapTile, CreateItemFrom(((Item *) elem->data)->type));
            self->DropInternal(self, itemType, --quantity, destroyItem);
        }
    }
}