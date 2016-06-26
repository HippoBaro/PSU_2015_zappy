/*
** Network_send.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Network
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:52:42 2016 Etienne Pasteur
** Last update Sun Jun 26 16:53:22 2016 Etienne Pasteur
*/

#include "Network.h"

extern bool	Send(Response *rep);

void		initNetworkPtrFuncSend(Network *this)
{
  this->Send = &Send;
}

extern bool	Send(Response *rep)
{
  if (send(rep->destFd, rep->message, strlen(rep->message), 0) !=
      (ssize_t) strlen(rep->message)) {
    Log(WARNING, "Message to socket: %d could not be sent", rep->destFd);
    rep->Free(rep);
    return (false);
  }
  else {
    Log(SUCCESS,
	"Message to socket: %d have been sent successfully Message was : \"%s\"",
	rep->destFd, rep->message);
    rep->Free(rep);
    return (true);
  }
}
