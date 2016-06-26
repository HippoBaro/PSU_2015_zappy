/*
** Transaction.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Request
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:12:28 2016 Etienne Pasteur
** Last update Sun Jun 26 17:16:01 2016 Etienne Pasteur
*/

#include "Drone.h"

static const struct s_request_invoke commands[] =
  {
    {MOVE,           (void *(*)(void *, Request *)) &Move,                                   NULL},
    {ROTATE,         (void *(*)(void *, Request *)) &Rotate,  (void *(*)(void *, Request *)) &CanRotate},
    {LOOK,           (void *(*)(void *, Request *)) &Look,                                   NULL},
    {LOOK_INVENTORY, (void *(*)(void *, Request *)) &ListInventory,                          NULL},
    {TAKE,           (void *(*)(void *, Request *)) &Take,    (void *(*)(void *, Request *)) &CanTake},
    {DROP,           (void *(*)(void *, Request *)) &Drop,    (void *(*)(void *, Request *)) &CanDrop},
    {EXPULSE,        (void *(*)(void *, Request *)) &Expulse, (void *(*)(void *, Request *)) &CanExpulse},
    {BROADCAST,      (void *(*)(void *, Request *)) &Broadcast,                              NULL},
    {INCANT,         (void *(*)(void *, Request *)) &Incant,  (void *(*)(void *, Request *)) &CanIncant},
    {FORK,           (void *(*)(void *, Request *)) &Fork,                                   NULL},
    {ASK_SLOT,       (void *(*)(void *, Request *)) &GetTeamSlot,                            NULL},
    {DIE,            (void *(*)(void *, Request *)) &Die,                                    NULL}
  };

static Response	*Execute(Request *request, Drone *drone)
{
  int		i;

  i = 0;
  while (i <= 11)
    {
      if (request->requestedAction == commands[i].requestAction)
	return (commands[i].invokeAction(drone, request));
      ++i;
    }
  return (NULL);
}

static Response	*Validate(Request *request, Drone *drone)
{
  int	i;

  i = 0;
  while (i <= 11)
    {
      if (request->requestedAction == commands[i].requestAction)
        {
	  if (commands[i].invokeValidate != NULL)
	    return commands[i].invokeValidate(drone, request);
        }
      ++i;
    }
  return NULL;
}

static Request	*RequestDidBecomeActive(Request *request, Drone *drone)
{
  Response	*res;

  if (request->requestedAction == INCANT)
    {
      res = CreateResponseFrom(request);
      res->message =
	asprintf("elevation en cours\nniveau actuel : %d", drone->level);
      res->Send(res);
    }
  return request;
}

static Request	*Sanitize(Request *self)
{
  size_t	len;

  if (self->message == NULL || (len = strlen(self->message)) == 0)
    return self;
  while (len > 0)
    {
      if (self->message[len] == '\n')
        {
	  self->message[len] = '\0';
	  return self;
        }
      --len;
    }
  return self;
}

void	InitRequestTransaction(Request *request)
{
  request->Execute = (void *(*)(Request *, void *)) &Execute;
  request->RequestDidBecomeActive =
    (Request *(*)(Request *, void *)) &RequestDidBecomeActive;
  request->Sanitize = &Sanitize;
  request->Validate = (void *(*)(struct t_Request *, void *)) &Validate;
}
