/*
** Move.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Drone/Action
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 15:44:02 2016 Etienne Pasteur
** Last update Sun Jun 26 15:45:16 2016 Etienne Pasteur
*/

#include "Generic.h"
#include "Drone.h"

static void	Turn90DegreesLeft (struct s_Drone *self)
{
  if ((int)(self->rotation - 90) < 0)
    self->rotation = (Rotation) 270;
  else
    self->rotation -= 90;
}

static void	Turn90DegreesRight (struct s_Drone *self)
{
  if (self->rotation + 90 >= 360)
    self->rotation = (Rotation) 0;
  else
    self->rotation += 90;
}

Response	*Move(struct s_Drone *self, Request *request)
{
  self->mapTile->RemoveDrone(self->mapTile, self);
  self->mapTile = self->mapTile->GetTopTile(self, self->mapTile->map);
  self->mapTile->AddDrone(self->mapTile, self);
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

Response	*Rotate(struct s_Drone *self, Request *request)
{
  if (strcmp(request->actionSubject, "gauche") == 0)
    self->Turn90DegreesLeft(self);
  else if (strcmp(request->actionSubject, "droite") == 0)
    self->Turn90DegreesRight(self);
  else
    return (CreateKoResponseFrom(request));
  return (CreateResponseFromFdWithMessage(self->socketFd, strdup("ok")));
}

void		InitDroneMove(Drone *selfDrone)
{
  selfDrone->Turn90DegreesLeft = &Turn90DegreesLeft;
  selfDrone->Turn90DegreesRight = &Turn90DegreesRight;
  selfDrone->GoTop = lambda(void, (Drone *self, Map *map), {
      self->mapTile = self->mapTile->GetTopTile(self, map);
    });
  selfDrone->GoRight = lambda(void, (Drone *self, Map *map), {
      self->mapTile = self->mapTile->GetRightTile(self, map);
    });
  selfDrone->GoBackwards = lambda(void, (Drone *self, Map *map), {
      self->mapTile = self->mapTile->GetBottomTile(self, map);
    });
  selfDrone->GoLeft = lambda(void, (Drone *self, Map *map), {
      self->mapTile = self->mapTile->GetLeftTile(self, map);
    });
}
