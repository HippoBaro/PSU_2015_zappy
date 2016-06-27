/*
** main.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 02:03:09 2016 Etienne Pasteur
** Last update Mon Jun 27 02:04:11 2016 Etienne Pasteur
*/

#include "Drone.h"
#include "ZappyServer.h"

int main(int ac, char **av)
{
  ZappyServer *server;

  server = CreateZappyServer();
  server->Configure(server, server->configuration
                    ->ParseFrom(server->configuration, ac, av)
                    ->Validate(server->configuration))
    ->Start(server)
    ->Free(server);
  return (EXIT_SUCCESS);
}
