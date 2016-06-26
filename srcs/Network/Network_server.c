/*
** Network_server.c for in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Network
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:56:20 2016 Etienne Pasteur
** Last update Sun Jun 26 16:56:45 2016 Etienne Pasteur
*/

#include "Network.h"

void serverMode(struct Network *this)
{
  int opt;

  opt = 1;
  if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
		 sizeof(opt)) < 0)
    Log(ERROR, "Setsockopt error");
  if (bind(this->_sock, (struct sockaddr *) &this->_adressage,
	   this->_adressageSize) != -1)
    {
      if (listen(this->_sock, 5) == -1)
	Log(ERROR, "Socket listen error");
    }
  else
    Log(ERROR, "Bind Socket error");
}
