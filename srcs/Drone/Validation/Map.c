/*
** Map.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Validation
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:40:46 2016 Etienne Pasteur
** Last update Sun Jun 26 15:41:27 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*CanExpulse (Drone *self, Request *request)
{
  bool	canExpulse;

  canExpulse = false;
  self->mapTile->drones->forEachElements(self->mapTile->drones,
					 lambda(void, (void *droneD, void *dat), {
					     if (droneD == self)
					       return;
					     canExpulse = true;
					   }), NULL);
  if (canExpulse)
    return (NULL);
  return (CreateKoResponseFrom(request));
}
