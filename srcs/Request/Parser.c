/*
** Parser.c for  in /home/antoine/zappy/srcs/Parser
**
** Made by antoine
** Login   <antoine@epitech.net>
**
** Started on  Mon Jun 13 14:37:03 2016 antoine
** Last update Mon Jun 13 18:13:51 2016 antoine
*/

#include "Request.h"
#include "Generic.h"
#include <stdio.h>
#include <string.h>

void	initRequestList(string *actions)
{
  actions[0] = "avance\n\0";
  actions[1] = "droite\n\0";
  actions[2] = "gauche\n\0";
  actions[3] = "voir\n\0";
  actions[4] = "inventaire\n\0";
  actions[5] = "prend\n\0";
  actions[6] = "pose\n\0";
  actions[7] = "expulse\n\0";
  actions[8] = "broadcast ";
  actions[9] = "incantation\n\0";
  actions[10] = "fork\n\0";
  actions[11] = "connect nbr\n\0";
  actions[12] = "-\n\0";
}

string		getSubject(string message)
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

string		cutMessage(string message)
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

void	reqMove(Request *req)
{
  req->requestedAction = MOVE;
  req->actionSubject = NULL;
}

void	reqRotateRight(Request *req)
{
  req->requestedAction = ROTATE;
  req->actionSubject = xmalloc(sizeof(char) * 6);
  req->actionSubject = "droite";
}

void	reqRotateLeft(Request *req)
{
  req->requestedAction = ROTATE;
  req->actionSubject = xmalloc(sizeof(char) * 6);
  req->actionSubject = "gauche";
}

void	reqLook(Request *req)
{
  req->requestedAction = LOOK;
  req->actionSubject = NULL;
}

void	reqLookInventory(Request *req)
{
  req->requestedAction = LOOK_INVENTORY;
  req->actionSubject = NULL;
}

void	reqExpulse(Request *req)
{
  req->requestedAction = EXPULSE;
  req->actionSubject = NULL;
}

void	reqIncant(Request *req)
{
  req->requestedAction = INCANT;
  req->actionSubject = NULL;
}

void	reqFork(Request *req)
{
  req->requestedAction = FORK;
  req->actionSubject = NULL;
}

void	reqAskSlot(Request *req)
{
  req->requestedAction = ASK_SLOT;
  req->actionSubject = NULL;
}

void		reqTake(Request *req)
{
  string	sub;
  req->requestedAction = TAKE;
  sub = getSubject(req->message);
}

void		reqDrop(Request *req)
{
  string	sub;
  req->requestedAction = DROP;
  sub = getSubject(req->message);

}

void		reqBroadcast(Request *req)
{
  string	sub;
  req->requestedAction = BROADCAST;
  sub = getSubject(req->message);
}

void		Parse(Request *request)
{
  int		i;
  string	actions[13];
  string	cut;
  void		(*doAction[13])(Request *);

  i = 0;
  doAction[0] = &reqMove;
  doAction[1] = &reqRotateRight;
  doAction[2] = &reqRotateLeft;
  doAction[3] = &reqLook;
  doAction[4] = &reqLookInventory;
  doAction[5] = &reqTake;
  doAction[6] = &reqDrop;
  doAction[7] = &reqExpulse;
  doAction[8] = &reqBroadcast;
  doAction[9] = &reqIncant;
  doAction[10] = &reqFork;
  doAction[11] = &reqAskSlot;
  doAction[12] = &reqLook;
  initRequestList(actions);
  cut = cutMessage(request->message);
  while (i++ < 12)
    if (strcmp(cut, actions[i]) == 0)
      doAction[i](request);
}
