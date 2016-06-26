/*
** Network_client.c for in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Network
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:48:18 2016 Etienne Pasteur
** Last update Sun Jun 26 16:48:33 2016 Etienne Pasteur
*/

#include "Network.h"

void clientMode(struct Network *this)
{
  if (connect(this->_sock, (struct sockaddr *) &this->_adressage,
	      sizeof(this->_adressage)) != -1) {
    Log(SUCCESS, "Connexion à %s sur le port %d",
	inet_ntoa(this->_adressage.sin_addr),
	htons(this->_adressage.sin_port));
  }
  else
    Log(ERROR, "Impossible de se connecter");
}
