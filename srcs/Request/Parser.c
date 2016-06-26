/*
** Parser.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Request
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:59:47 2016 Etienne Pasteur
** Last update Sun Jun 26 17:06:01 2016 Etienne Pasteur
*/

#include "Request.h"

static const struct s_command_string requestsArray[] =
  {
    {"avance",      MOVE,           NULL,       false,  7},
    {"droite",      ROTATE,         "droite",   true,   7},
    {"gauche",      ROTATE,         "gauche",   true,   7},
    {"voir",        LOOK,           NULL,       false,  7},
    {"inventaire",  LOOK_INVENTORY, NULL,       false,  1},
    {"prend",       TAKE,           NULL,       true,   7},
    {"pose",        DROP,           NULL,       true,   7},
    {"expulse",     EXPULSE,        NULL,       false,  7},
    {"broadcast",   BROADCAST,      NULL,       true,   7},
    {"incantation", INCANT,         NULL,       false,  300},
    {"fork",        FORK,           NULL,       false,  42},
    {"connect_nbr", ASK_SLOT,       NULL,       false,  0},
    {"-",           DIE,            NULL,       false,  0}
  };

static string	getSubject(string message)
{
  int		i;
  int		start;

  i = 0;
  start = -1;
  while (message[i] != '\0')
    {
      if (message[i] == ' ' || message[i] == '\t')
        {
	  start = ++i;
	  break;
        }
      ++i;
    }
  if (start == -1)
    return (NULL);
  return (strndup(message + start, strlen(message) - start));
}

static string	cutMessage(string message)
{
  string	str;
  size_t	i;

  i = 0;
  while (message[i] && message[i] != ' ')
    i++;
  str = xmalloc((size_t) (i + 1));
  strncpy(str, message, i);
  str[i] = '\0';
  return (str);
}

static void	SetRequestInfo(Request *r, Action ac, string msg, bool setMsg)
{
  r->requestedAction = ac;
  if (setMsg)
    {
      if (msg == NULL)
	r->actionSubject = getSubject(r->message);
      else
	r->actionSubject = strdup(msg);
    }
  else
    r->actionSubject = NULL;
}

Request		*ParseRequest(Request *request)
{
  int		i;
  string	cut;

  i = 0;
  cut = cutMessage(request->message);
  while (i <= 12)
    {
      if (strcmp(cut, requestsArray[i].str) == 0)
	{
	  request->absoluteActionTime = requestsArray[i].absoluteTime;
	  SetRequestInfo(request,
			 requestsArray[i].action,
			 requestsArray[i].staticSubject,
			 requestsArray[i].setSubject);
	}
      ++i;
    }
  xfree(cut, strlen(cut));
  return request;
}
