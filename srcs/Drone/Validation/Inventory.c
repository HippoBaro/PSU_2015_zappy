//
// Created by barrauh on 6/25/16.
//

#include "Drone.h"

Response *CanTake (struct s_Drone *self, Request *request) {
    t_list *elem;
    ItemType itemType;

    itemType = ItemFromString(request->actionSubject);
    if (itemType == UNKNOWN_ITEMTYPE)
        return CreateKoResponseFrom(request);
    elem = self->mapTile->ressources->firstElementFromPredicate(self->mapTile->ressources, lambda(bool, (void *ress, void *dat), {
        return (bool) (((Item *) ress)->type == itemType && ((Item *) ress)->quantity > 0);
    }), NULL);
    if (elem == NULL || ((Item *) elem->data)->quantity < 1)
        return CreateKoResponseFrom(request);
    return NULL;
}

Response *CanDrop (struct s_Drone *self, Request *request) {
    t_list *elem;
    ItemType itemType;

    itemType = ItemFromString(request->actionSubject);
    if (itemType == UNKNOWN_ITEMTYPE)
        return CreateKoResponseFrom(request);
    elem = self->inventory->firstElementFromPredicate(self->inventory, lambda(bool, (void *itemPred, void *dat), {
        return (bool)(((Item *)itemPred)->type == itemType);
    }), NULL);
    if (elem == NULL || elem->data == NULL || ((Item *)elem->data)->quantity < 1)
        return CreateKoResponseFrom(request);
    return NULL;
}