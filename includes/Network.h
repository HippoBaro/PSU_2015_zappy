//
// Created by pasteu_e on 12/06/16.
//

#ifndef PSU_2015_ZAPPY_NETWORK_H
# define PSU_2015_ZAPPY_NETWORK_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

# include "Generic.h"
# include "LinkedList.h"
# include "Response.h"
# include "Request.h"

# define BUFFSIZE 8096
int masterSocket;

typedef enum {
    SERVER,
    CLIENT
} NetworkType;

typedef struct s_dataServer {
    struct Network *net;
    fd_set rfds;
    Request *req;
} t_dataServer;

typedef struct s_variable {
    t_dataServer *someData;
    Request *req;
    int sd;
    ssize_t valread;
    char buffer[BUFFSIZE];
    int maxfd;
    t_list *tmp;
} t_variable;

typedef struct s_client {
    int _sock;
    struct sockaddr_in _adressage;
    socklen_t _adressageSize;
} t_client;

typedef struct Network {
    int _sock;
    struct sockaddr_in _adressage;
    socklen_t _adressageSize;
    uint16_t _port;
    char *_addr;
    NetworkType _type;
    LinkedList *_clientSock;

    Request *(*Receive)(struct Network *this, struct timeval *tv);
    bool (*Send)(struct e_Response *rep);
    void (*DeleteNetwork)(struct Network *this);
    void (*Disconnect)(struct Network *this, int fd);
} Network;

extern Network *CreateNetwork(NetworkType type, uint16_t port, char *addr);

bool Send(Response *rep);

void initNetworkPtrFuncReceive(Network *this);

void initNetworkPtrFuncSend(Network *this);

void INThandler(int sig);

void PIPEhandler(int sig);

void createSocket(struct Network *this);

void serverMode(struct Network *this);

void clientMode(struct Network *this);

void addClientToList(struct Network *this, Request **req);

bool checkServerConnectionAndMessage(void *elem, void *userData);

#endif //PSU_2015_ZAPPY_NETWORK_H
