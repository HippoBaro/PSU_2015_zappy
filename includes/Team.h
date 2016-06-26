/*
** Team.h for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:35:23 2016 Etienne Pasteur
** Last update Mon Jun 27 00:37:48 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_TEAM_H
# define PSU_2015_ZAPPY_TEAM_H

# include "Generic.h"
# include "LinkedList.h"

typedef struct			s_Team {
    LinkedList(uint32_t)	*nextslots;
    int				currentUsedSlot;
    int				maxSlot;
    string			teamName;
    void			(*Free)(struct s_Team *self);
    int				(*GetAvailableSlots)(struct s_Team *self);
    bool			(*CanAddNewDrone)(struct s_Team *self);
    struct s_Team		*(*UpdateTeam)(struct s_Team *self);
    struct s_Team		*(*ScheduleAddSlot)(struct s_Team *, double);
}				Team;

void				DestroyTeam(Team *self);
Team				*CreateTeamFrom(string name, int maxSlot);

#endif //PSU_2015_ZAPPY_TEAM_H
