//
// Created by barrauh on 6/23/16.
//

#include "Generic.h"

#ifndef PSU_2015_ZAPPY_TEAM_H
#define PSU_2015_ZAPPY_TEAM_H

typedef struct s_Team {
    int         currentUsedSlot;
    int         maxSlot;
    string      teamName;
    void        (*Free)(struct s_Team *self);
    int         (*GetAvailableSlots)(struct s_Team *self);
    bool        (*CanAddNewDrone)(struct s_Team *self);
}               Team;

void            DestroyTeam(Team *self);
Team            *CreateTeamFrom(string name, int maxSlot);

#endif //PSU_2015_ZAPPY_TEAM_H
