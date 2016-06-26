/*
** Incant.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 13:43:56 2016 Etienne Pasteur
** Last update Sun Jun 26 15:46:11 2016 Etienne Pasteur
*/

#include "Drone.h"

Response *Incant(struct s_Drone *self, Request *request)
{
  self->mapTile->drones->forEachElements(
					 self->mapTile->drones,
					 lambda(void, (void *drone, void *dat), {
					     if (((Drone *)drone)->level == self->level)
					       ((Drone *)drone)->level++;
					   }), NULL);
  return (NULL);
}
