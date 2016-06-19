//
// Created by barrauh on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_REQUEST_H
#define PSU_2015_ZAPPY_REQUEST_H

#include "Generic.h"
#include "Timer.h"
#include "LinkedList.h"

typedef struct          s_ZappyServer ZappyServer;

typedef struct          t_Request {
    RequestType         type;
    string              message;
    int                 socketFd;
    Action              requestedAction;
    string              actionSubject;
    int                 absoluteActionTime;
    Timer               *timer;
    uint64_t            (*GetCompletionTime)(struct t_Request *self, ZappyServer *server);
    bool                (*Validate)(struct t_Request *self);
    void                *(*Execute)(struct t_Request *self, void *drone);
    struct t_Request    *(*Parse)(struct t_Request *self);
    void                (*Free)(struct t_Request *self);
}                       Request;

struct s_command_string {
    string	str;
    void		(*doAction)(Request *);
    int     absoluteTime;
};

Request *CreateRequest(string message, int socketFd);
Request *ParseRequest(Request *request);
void    DestroyRequest(Request *request);

#endif //PSU_2015_ZAPPY_REQUEST_H
