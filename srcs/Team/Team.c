//
// Created by barrauh on 6/23/16.
//

#include "Team.h"

void            DestroyTeam(Team *self) {
    if (self->teamName != NULL)
        xfree(self->teamName, strlen(self->teamName));
    xfree(self, sizeof(Team));
}

static int      GetAvailableSlots(Team *self) {
    return self->maxSlot - self->currentUsedSlot;
}

static bool     CanAddNewDrone(Team *self) {
    if (self->currentUsedSlot < self->maxSlot)
        return true;
    return false;
}

Team            *CreateTeamFrom(string name, int maxSlot) {
    Team    *ret;

    ret = xmalloc(sizeof(Team));
    ret->teamName = strdup(name);
    ret->currentUsedSlot = 0;
    ret->maxSlot = maxSlot;
    ret->CanAddNewDrone = &CanAddNewDrone;
    ret->GetAvailableSlots = &GetAvailableSlots;
    ret->Free = &DestroyTeam;
    return ret;
}