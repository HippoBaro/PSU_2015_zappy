/*
** Move.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Validation
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:42:30 2016 Etienne Pasteur
** Last update Mon Jun 27 01:52:40 2016 Etienne Pasteur
*/

#include "Drone.h"

Response	*CanRotate(struct s_Drone *self, Request *request)
{
  if (strcmp(request->actionSubject, "gauche") == 0)
    return (NULL);
  else if (strcmp(request->actionSubject, "droite") == 0)
    return (NULL);
  return (CreateKoResponseFrom(request));
}
