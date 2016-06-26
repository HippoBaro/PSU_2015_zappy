/*
** clientGraph.c for zap in /home/pasteu_e/rendu/PSU_2015_zappy/GraphClient
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 23:02:57 2016 Etienne Pasteur
** Last update Sun Jun 26 23:05:29 2016 Etienne Pasteur
*/

#include "GraphClient.h"

void		parse_command(char *str, t_ecran *val)
{
  char		*cmd;
  char		*context;
  int		i;
  t_flags	flags[] = {
    {"msz", msz},
    {"sgt", sgt},
    {"bct", bct}
  };

  i = 0;
  if (str[0])
    {
      cmd = strtok_r(str, " ", &context);
      while (i < 3)
	{
	  if (strcmp(cmd, flags[i].cmd) == 0)
	    flags[i].ptrF(context, val);
	  i++;
        }
    }
}

void		initConnectionWithServer(t_valGraph *v)
{
  if (v->req == NULL || strcmp(v->req->message, "BIENVENUE\n") != 0)
    {
      if (v->req != NULL)
	v->req->Free(v->req);
      Log(ERROR, "Incorrect connection to server");
    }
  v->req->Free(v->req);
  Response *tmp = CreateEmptyResponse();
  tmp->destFd = v->net->_sock;
  tmp->message = strdup("GRAPHIC\n");
  v->net->Send(tmp);
}

bool		dataFromServer(t_valGraph *v)
{
  v->str_copy = strdup(v->req->message);
  v->tmp_string = v->str_copy;
  while ((v->token = strsep(&v->str_copy, "\n")))
    parse_command(v->token, &v->val);
  free(v->tmp_string);
  if (v->req->message != NULL && v->req->message[0] == '-' &&
      v->req->message[1] == '\0')
    {
      v->req->Free(v->req);
      return (false);
    }
  v->req->Free(v->req);
  return (true);
}

int		main(int argc, char **argv)
{
  t_valGraph	v;

  v.net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
  initVarGraph(&v);
  initConnectionWithServer(&v);
  while (1)
    {
      v.tv.tv_sec = 0;
      v.tv.tv_usec = 5000;
      v.req = v.net->Receive(v.net, &v.tv);
      if (v.req != NULL)
	{
	  if (dataFromServer(&v) == false)
	    break;
	}
      else if (displayGraph(&v) == false)
	break;
    }
  freeVariableGraph(&v);
  return (0);
}
