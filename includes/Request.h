//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_REQUEST_H
#define PSU_2015_ZAPPY_REQUEST_H

#include "Generic.h"

typedef struct t_Request {
    string      message;
    int         socketFd;
    Action      requestedAction;
    string      actionSubject;
    bool        (*Validate)(struct t_Request *self);
    void        (*Parse)(struct t_Request *self);
    void        (*Free)(struct t_Request *self);
}               Request;

struct s_command_string {
  string	str;
  void		(*doAction)(Request *);
};

Request *CreateRequest(string message, int socketFd);

#endif //PSU_2015_ZAPPY_REQUEST_H
