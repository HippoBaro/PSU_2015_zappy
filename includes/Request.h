//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_REQUEST_H
#define PSU_2015_ZAPPY_REQUEST_H

#include "Generic.h"

typedef struct          s_ZappyServer ZappyServer;

typedef struct          t_Request {
    ZappyServer         *server;
    RequestType         type;
    string              message;
    int                 socketFd;
    Action              requestedAction;
    string              actionSubject;
    bool                (*Validate)(struct t_Request *self);
    struct t_Request    *(*Parse)(struct t_Request *self);
    void                (*Free)(struct t_Request *self);
}                       Request;

struct s_command_string {
  string	str;
  void		(*doAction)(Request *);
};

Request *CreateRequest(string message, int socketFd);
Request *ParseRequest(Request *request);
void    DestroyRequest(Request *request);

#endif //PSU_2015_ZAPPY_REQUEST_H
