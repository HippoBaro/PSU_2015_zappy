/*
** Map.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Validation
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:40:46 2016 Etienne Pasteur
** Last update Mon Jun 27 01:52:17 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*CanExpulse (Drone *self, Request *request)
{
  bool		canExpulse;

  canExpulse = false;
  ForEach(self->mapTile->drones, droneD, {
      if (droneD == self)
	return;
      canExpulse = true;
    });
  if (canExpulse)
    return (NULL);
  return (CreateKoResponseFrom(request));
}
