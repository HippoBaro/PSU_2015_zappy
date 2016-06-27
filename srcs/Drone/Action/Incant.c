/*
** Incant.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 13:43:56 2016 Etienne Pasteur
** Last update Mon Jun 27 01:36:26 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*Incant(struct s_Drone *self, Request *request)
{
  ForEach(self->mapTile->drones, drone, {
      if (((Drone *)drone)->level == self->level)
	((Drone *)drone)->level++;
    });
  return (NULL);
}
