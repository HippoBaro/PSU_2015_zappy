/*
** Parser.c for  in /home/antoine/zappy/srcs/Parser
**
** Made by antoine
** Login   <antoine@epitech.net>
**
** Started on  Mon Jun 13 14:37:03 2016 antoine
** Last update Mon Jun 13 19:45:20 2016 antoine
*/

#include "Request.h"
#include "Generic.h"
#include <stdio.h>
#include <string.h>


static string	getSubject(string message)
{
  string	str;
  int		i;
  int		x;

  i = 0;
  x = 0;
  while (message[i++] != ' ');
  str = xmalloc(sizeof(char) * strlen(message) - i);
  while (message[i])
    str[x++] = message[i++];
  return (str);
}

static string	cutMessage(string message)
{
  string	str;
  int		i;
  int		x;

  i = 0;
  while (message[i] != '\n' && message[i] != ' ')
      i++;
  str = xmalloc(sizeof(char) * i + 1);
  x = i;
  i = 0;
  while (i < x)
    {
      str[i] = message[i];
      i++;
    }
  str[i] = '\n';
  //  str[i + 1] = '\0';
  return (str);
}

static void	reqMove(Request *req)
{
  req->requestedAction = MOVE;
  req->actionSubject = NULL;
}

static void	reqRotateRight(Request *req)
{
  req->requestedAction = ROTATE;
  req->actionSubject = xmalloc(sizeof(char) * 6);
  req->actionSubject = "droite";
}

static void	reqRotateLeft(Request *req)
{
  req->requestedAction = ROTATE;
  req->actionSubject = xmalloc(sizeof(char) * 6);
  req->actionSubject = "gauche";
}

static void	reqLook(Request *req)
{
  req->requestedAction = LOOK;
  req->actionSubject = NULL;
}

static void	reqLookInventory(Request *req)
{
  req->requestedAction = LOOK_INVENTORY;
  req->actionSubject = NULL;
}

static void	reqExpulse(Request *req)
{
  req->requestedAction = EXPULSE;
  req->actionSubject = NULL;
}

static void	reqIncant(Request *req)
{
  req->requestedAction = INCANT;
  req->actionSubject = NULL;
}

static void	reqFork(Request *req)
{
  req->requestedAction = FORK;
  req->actionSubject = NULL;
}

static void	reqAskSlot(Request *req)
{
  req->requestedAction = ASK_SLOT;
  req->actionSubject = NULL;
}

static void	reqTake(Request *req)
{
  string	sub;
  req->requestedAction = TAKE;
  sub = getSubject(req->message);
  req->actionSubject = sub;
}

static void	reqDrop(Request *req)
{
  string	sub;
  req->requestedAction = DROP;
  sub = getSubject(req->message);
  req->actionSubject = sub;
}

static void	reqBroadcast(Request *req)
{
  string	sub;
  req->requestedAction = BROADCAST;
  sub = getSubject(req->message);
  req->actionSubject = sub;
}

static void	reqDeath(Request *req)
{
  req->requestedAction = DIE;
  req->actionSubject = NULL;
}

static const struct s_command_string toStringRequests[] =
  {
    { "avance\n\0", &reqMove},
    { "droite\n\0", &reqRotateRight },
    { "gauche\n\0", &reqRotateLeft },
    { "voir\n\0", &reqLook },
    { "inventaire\n\0", &reqLookInventory },
    { "prend\n\0", &reqTake },
    { "pose\n\0", &reqDrop },
    { "expulse\n\0", &reqExpulse },
    { "broadcast\n\0", &reqBroadcast },
    { "incantation\n\0", &reqIncant },
    { "fork\n\0", &reqFork },
    { "connect nbr\n\0", &reqLook },
    { "-\n\0", &reqDeath }
  };

void		Parse(Request *request)
{
  int		i;
  string	cut;

  i = 0;
  cut = cutMessage(request->message);
  while (i++ < 12)
    if (strcmp(cut, toStringRequests[i].str) == 0)
      toStringRequests[i].doAction(request);
}
