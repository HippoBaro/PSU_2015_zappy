/*
** Network_receive.c for in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Network
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:48:52 2016 Etienne Pasteur
** Last update Sun Jun 26 16:52:08 2016 Etienne Pasteur
*/

#include <errno.h>
#include "Network.h"

extern Request	*Receive(struct Network *this, struct timeval *tv);

void		initNetworkPtrFuncReceive(Network *this)
{
  this->Receive = &Receive;
}

static Request	*Receive_server(struct Network *this,
				t_variable *var)
{
  if (FD_ISSET(this->_sock, &var->someData->rfds)) {
    addClientToList(this, &var->req);
    xfree(var->someData, sizeof(t_dataServer));
    return (var->req);
  }
  var->tmp = this->_clientSock->firstElementFromPredicate(
							  this->_clientSock, &checkServerConnectionAndMessage,
							  var->someData);
  if (var->tmp != NULL) {
    if (var->someData->req->message != NULL &&
	var->someData->req->message[0] == '-')
      this->_clientSock->freeThisElem(this->_clientSock,
				      lambda(void, (void *data), {
					  xfree((t_client *) data,
						sizeof(t_client));
					}), var->tmp);
    var->req = CreateRequest(strdup(var->someData->req->message),
			     var->someData->req->socketFd);
    var->req->type = var->someData->req->type;
    var->someData->req->Free(var->someData->req);
    xfree(var->someData, sizeof(t_dataServer));
    return (var->req);
  }
  xfree(var->someData, sizeof(t_dataServer));
  return (NULL);
}

static Request	*Receive_client(struct Network *this,
				t_variable *var)
{
  if (FD_ISSET(this->_sock, &var->someData->rfds)) {
    if ((var->valread = read(this->_sock, var->buffer, BUFFSIZE - 1)) == 0) {
      Log(WARNING, "Server disconnected");
      close(this->_sock);
      xfree(var->someData, sizeof(t_dataServer));
      var->req = CreateRequest(strdup("-"), this->_sock);
      return (var->req);
    }
    else {
      var->buffer[var->valread] = '\0';
      xfree(var->someData, sizeof(t_dataServer));
      var->req = CreateRequest(strdup(var->buffer), this->_sock);
      return (var->req);
    }
  }
  xfree(var->someData, sizeof(t_dataServer));
  return (NULL);
}

static void	initVarNetwork(struct Network *this, t_variable *var)
{
  var->someData = xmalloc(sizeof(t_dataServer));
  var->someData->net = this;
  var->someData->req = NULL;
  FD_ZERO(&var->someData->rfds);
  FD_SET(this->_sock, &var->someData->rfds);
  var->maxfd = this->_sock;
}

extern Request	*Receive(struct Network *this, struct timeval *tv)
{
  t_variable	var;

  initVarNetwork(this, &var);
  if (this->_type == SERVER)
      ForEach(this->_clientSock, elem, {
					   var.sd = ((t_client *) elem)->_sock;
					   FD_SET(var.sd, &var.someData->rfds);
					   if (var.sd > var.maxfd)
					     var.maxfd = var.sd;
					 });
  if (tv != NULL)
    Log(INFORMATION, "Nxt tm is %lu s and %lu us.", tv->tv_sec, tv->tv_usec);
  else
    Log(INFORMATION, "Next timeout is infinite.");
  if (select(var.maxfd + 1, &var.someData->rfds, NULL, NULL, tv) == -1)
    Log(ERROR, "Select error : errno is %d", errno);
  if (this->_type == SERVER)
    return (Receive_server(this, &var));
  else if (this->_type == CLIENT)
    return (Receive_client(this, &var));
  xfree(var.someData, sizeof(t_dataServer));
  return (NULL);
}
