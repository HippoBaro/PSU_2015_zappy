/*
** Request.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Request
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:06:27 2016 Etienne Pasteur
** Last update Mon Jun 27 02:12:32 2016 Etienne Pasteur
*/

#include "ZappyServer.h"

static uint64_t	GetCompletionTime(Request *self, ZappyServer *server)
{
  double	dlyAsSec;
  uint64_t	ret;

  dlyAsSec = (double)self->absoluteActionTime *
    server->configuration->temporalDelay;
  Log(INFORMATION, "Request time is %lu", dlyAsSec * 1000000);
  ret = (uint64_t) (dlyAsSec * 1000000);
  return (ret);
}

void		DestroyRequest(Request *request)
{
  if (request->message != NULL)
    xfree(request->message, strlen(request->message) + 1);
  if (request->actionSubject != NULL)
    xfree(request->actionSubject, strlen(request->actionSubject));
  xfree(request->timer, sizeof(Timer));
  xfree(request, sizeof(Request));
}

string		GetRequestAsString(Request *request)
{
  string	ret;

  if (request == NULL || request->message == NULL)
    return strdup("");
  ret = strdup(request->message);
  request->Free(request);
  return (ret);
}

Request		*CreateRequest(string message, int socketFd)
{
  Request	*ret;

  ret = xmalloc(sizeof(Request));
  ret->type = UNKNOWN_REQUESTTYPE;
  ret->message = message;
  ret->socketFd = socketFd;
  ret->requestedAction = UNKNOWN_ACTION;
  ret->actionSubject = NULL;
  ret->timer = NULL;
  ret->absoluteActionTime = -1;
  ret->Parse = &ParseRequest;
  ret->GetCompletionTime = &GetCompletionTime;
  ret->Free = &DestroyRequest;
  InitRequestTransaction(ret);
  return (ret);
}
