/*
** Response.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Response
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:16:50 2016 Etienne Pasteur
** Last update Sun Jun 26 17:18:17 2016 Etienne Pasteur
*/

#include "Generic.h"
#include "Response.h"
#include "Network.h"

void		DestroyResponse(Response *response)
{
  if (response->message != NULL)
    xfree(response->message, strlen(response->message));
  xfree(response, sizeof(Response));
}

Response	*CreateResponseFrom(Request *request)
{
  Response	*ret;

  ret = CreateEmptyResponse();
  ret->destFd = request->socketFd;
  return (ret);
}

Response	*CreateResponseFromFdWithMessage(int fd, string message)
{
  Response	*ret;

  ret = CreateEmptyResponse();
  ret->destFd = fd;
  ret->message = message;
  return (ret);
}

Response	*CreateKoResponseFrom(Request *request)
{
  Response	*ret;

  ret = CreateResponseFrom(request);
  ret->message = strdup("ko");
  return (ret);
}

Response	*CreateEmptyResponse()
{
  Response	*ret;

  ret = xmalloc(sizeof(Response));
  ret->message = NULL;
  ret->destFd = -1;
  ret->Send = lambda(bool, (Response *self), {
      self->message = strappend(self->message, "\n", FIRST);
      return Send(self);
    });
  ret->Free = &DestroyResponse;
  return (ret);
}
