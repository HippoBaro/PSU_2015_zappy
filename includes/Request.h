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
    void                *(*Validate)(struct t_Request *self, void *drone);
    void                *(*Execute)(struct t_Request *self, void *drone);
    struct t_Request    *(*RequestDidBecomeActive)(struct t_Request *self, void *drone);
    struct t_Request    *(*Parse)(struct t_Request *self);
    struct t_Request    *(*Sanitize)(struct t_Request *self);
    void                (*Free)(struct t_Request *self);
}                       Request;

struct s_request_invoke {
    Action	        requestAction;
    void		    *(*invokeAction)(void *drone, Request *self);
    void		    *(*invokeValidate)(void *drone, Request *self);
};

struct s_command_string {
    string	        str;
    Action          action;
    string          staticSubject;
    bool            setSubject;
    int             absoluteTime;
};

Request *CreateRequest(string message, int socketFd);
Request *ParseRequest(Request *request);
void    DestroyRequest(Request *request);
void InitRequestTransaction(Request *request);

#endif //PSU_2015_ZAPPY_REQUEST_H
