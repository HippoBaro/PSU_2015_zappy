//
// Created by pasteu_e on 12/06/16.
//

#ifndef PSU_2015_ZAPPY_NETWORK_H
# define PSU_2015_ZAPPY_NETWORK_H

# include <string.h>

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>

# include "Generic.h"
# include "LinkedList.h"
# include "Response.h"
# include "Request.h"

#define PORT 8080

int masterSocket; //variable to pass to sigint handler in cause of Ctrl+C to close the connection

typedef enum {
    SERVER,
    CLIENT
} NetworkType;

typedef struct s_dataServer {
    struct Network *net;
    fd_set rfds;
    Request *req;
} t_dataServer;

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

    Request *(*Receive)(struct Network *this, int timeout);
    bool (*Send)(struct e_Response *rep);
    void (*DeleteNetwork)(struct Network *this);
}               Network;

Network *CreateNetwork(NetworkType type, uint16_t port, char *addr);

#endif //PSU_2015_ZAPPY_NETWORK_H
