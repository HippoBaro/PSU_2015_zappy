/*
** Configuration.c for in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/ZappyServer
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 17:20:29 2016 Etienne Pasteur
** Last update Sun Jun 26 17:31:31 2016 Etienne Pasteur
*/

#include <getopt.h>
#include "ZappyServer.h"

static LinkedList(string)	*GetTeamsFromArg(string team)
{
  string			pch;
  LinkedList(string)		*teams;

  if (team == NULL || strlen(team) == 0)
    return (NULL);
  teams = CreateLinkedList();
  pch = strtok (team, " \t");
  while (pch != NULL)
    {
      teams->addElemFront(teams, strdup(pch));
      pch = strtok (team, " ");
    }
  return (teams);
}

static Configuration	*ParseFrom(Configuration *config, int ac, char **av)
{
  int			c;
  int			index;

  opterr = 0;
  Log(INFORMATION, "Parsing configuration...");
  while ((c = getopt (ac, av, "p:x:y:c:t:n:s:")) != -1)
    {
      if (c == 'p')
	config->port = atoi(optarg);
      else if (c == 'x')
	config->worldWidth = atoi(optarg);
      else if (c == 'y')
	config->worldHeight = atoi(optarg);
      else if (c == 'c')
	config->initialClientPerTeam = atoi(optarg);
      else if (c == 't')
	config->temporalDelay = atof(optarg);
      else if (c == 's')
	config->seed = atomicdup(int, atoi(optarg));
      else if (c == 'n')
	config->teamNames = GetTeamsFromArg(optarg);
    }
  for (index = optind; index < ac; index++)
    printf ("Non-option argument %s\n", av[index]);
  return config;
}

static Configuration   *Validate(Configuration *config)
{
  if (config->initialClientPerTeam < 1)
    Log(ERROR, "Initial per-team available slots must be at least 1.");
  if (config->worldHeight < 4 || config->worldWidth < 4)
    Log(ERROR, "Invalid requested map size. A map should be a least 5x5.");
  if (config->port < 1000)
    Log(ERROR, "Unable to bind socket. Sub-1000 ports numbers are reserved.");
  if (config->port > 65535)
    Log(ERROR, "Illegal port number.");
  if (config->teamNames == NULL ||
      config->teamNames->countLinkedList(config->teamNames) > 1)
    Log(ERROR, "You must provide as least 1 team name.");
  if (config->temporalDelay < 0)
    Log(ERROR, "Temporal factor must be > 0.");
  Log(INFORMATION, "Configuration was successfully validated.");
  return config;
}

void			DestroyConfiguration(Configuration *config)
{
  if (config->teamNames != NULL)
    {
      config->teamNames->freeAll(config->teamNames,
				 lambda(void, (void *elem), {
				     xfree(elem, strlen(elem));
				   }));
      config->teamNames->Free(config->teamNames);
    }
  if (config->seed != NULL)
    xfree(config->seed, sizeof(int));
  xfree(config, sizeof(Configuration));
}

Configuration		*CreateConfiguration()
{
  Configuration		*ret;

  ret = xmalloc(sizeof(Configuration));
  ret->port = 0;
  ret->seed = NULL;
  ret->temporalDelay = 100;
  ret->worldHeight = 0;
  ret->worldWidth = 0;
  ret->teamNames = NULL;
  ret->Validate = &Validate;
  ret->ParseFrom = &ParseFrom;
  ret->Free = &DestroyConfiguration;
  return ret;
}
