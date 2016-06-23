//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

void createSocket(struct Network *this) {
    this->_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sock != -1) {
        masterSocket = this->_sock;
        this->_adressage.sin_addr.s_addr = (this->_type == SERVER ? htonl(
                INADDR_ANY) : inet_addr(this->_addr));
        this->_adressage.sin_family = AF_INET;
        this->_adressage.sin_port = htons(this->_port);
        this->_adressageSize = sizeof(this->_adressage);
        if (this->_type == SERVER) {
            this->_clientSock = CreateLinkedList();
            serverMode(this);
        }
        else if (this->_type == CLIENT)
            clientMode(this);
    }
    else
        Log(ERROR, "Socket creation error");
}

void addClientToList(struct Network *this, Request **req) {
    t_client *newClient;

    newClient = xmalloc(sizeof(t_client));
    newClient->_adressageSize = sizeof(newClient->_adressage);
    newClient->_sock = accept(this->_sock,
                              (struct sockaddr *) &newClient->_adressage,
                              &newClient->_adressageSize);
    if (newClient->_sock == -1)
        Log(ERROR, "Accept socket client error");
    else {
        Log(SUCCESS, "Un client se connecte avec la socket %d de %s:%d.",
            newClient->_sock,
            inet_ntoa(newClient->_adressage.sin_addr),
            htons(newClient->_adressage.sin_port));
        this->_clientSock->addElemFront(this->_clientSock, (void *) newClient);
        *req = CreateRequest(NULL, newClient->_sock);
        (*req)->type = NEW_CLIENT;
    }
}

bool checkServerConnectionAndMessage(void *elem, void *userData) {
    t_dataServer *someData;
    int sd;
    ssize_t valread;
    char buffer[BUFFSIZE];

    someData = (t_dataServer *) userData;
    sd = ((t_client *) elem)->_sock;
    if (FD_ISSET(sd, &someData->rfds)) {
        if ((valread = read(sd, buffer, 1024)) == 0) {
            someData->req = CreateRequest(strdup("-"), sd);
            someData->req->type = EXISTING_CLIENT;
            Log(INFORMATION, "Host disconnected , ip %s , port %d",
                inet_ntoa(((t_client *) elem)->_adressage.sin_addr),
                ntohs(((t_client *) elem)->_adressage.sin_port));
            close(sd);
            return (true);
        }
        buffer[valread] = '\0';
        Log(INFORMATION, "MSG from client with socket : %d -> %s.", sd,
            buffer);
        someData->req = CreateRequest(strdup(buffer), sd);
        someData->req->type = EXISTING_CLIENT;
        return (true);
    }
    return (false);
}