/*
** Response.h for za in /home/pasteu_e/rendu/PSU_2015_zappy/includes
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Mon Jun 27 00:22:28 2016 Etienne Pasteur
** Last update Mon Jun 27 00:25:09 2016 Etienne Pasteur
*/

#ifndef PSU_2015_ZAPPY_RESPONSE_H
# define PSU_2015_ZAPPY_RESPONSE_H

# include "Generic.h"
# include "LinkedList.h"
# include "Request.h"

typedef struct s_ZappyServer	ZappyServer;

typedef struct			e_Response
{
  ZappyServer			*server;
  string			 message;
  int				destFd;
  bool				(*Send)(struct e_Response *self);
  void				(*Free)(struct e_Response *self);
}				Response;

Response			*CreateEmptyResponse();
Response			*CreateResponseFrom(Request *request);
Response			*CreateKoResponseFrom(Request *request);
Response			*CreateResponseFromFdWithMessage(int fd, string message);

#endif //PSU_2015_ZAPPY_RESPONSE_H
