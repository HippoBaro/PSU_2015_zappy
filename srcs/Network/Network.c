//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

static void DeleteNetwork(struct Network *this);

static void Disconnect(struct Network *this, int fd);

void initNetworkPtrFunc(Network *this) {
    initNetworkPtrFuncSend(this);
    initNetworkPtrFuncReceive(this);
    this->Disconnect = &Disconnect;
    this->DeleteNetwork = &DeleteNetwork;
}

Network *CreateNetwork(NetworkType type, uint16_t port, char *addr) {
    Network *this;

    this = xmalloc(sizeof(Network));
    initNetworkPtrFunc(this);
    this->_type = type;
    this->_port = port;
    this->_addr = addr;
    createSocket(this);
    return (this);
}

static void Disconnect(struct Network *this, int fd) {
    t_list *tmp;

    shutdown(fd, 2);
    close(fd);
    tmp = this->_clientSock->firstElementFromPredicate(
            this->_clientSock, lambda(bool, (void *elem, void *userData), {
                if (((t_client *) elem)->_sock == fd)
                    return (true);
                else
                    return (false);
            }), NULL);
    if (tmp != NULL) {
        Log(INFORMATION, "Host disconnected , ip %s , port %d",
            inet_ntoa(((t_client *) tmp->data)->_adressage.sin_addr),
            ntohs(((t_client *) tmp->data)->_adressage.sin_port));
        this->_clientSock->freeThisElem(this->_clientSock,
                                        lambda(void, (void *data), {
                                            xfree((t_client *) data,
                                                  sizeof(t_client));
                                        }), tmp);
    }
}

static void DeleteNetwork(struct Network *this) {
    if (this->_type == SERVER) {
        this->_clientSock->forEachElements(
                this->_clientSock,
                lambda(void,
                       (void *elem, void *userData),
                       {
                           shutdown(
                                   ((t_client *) elem)->_sock,
                                   2);
                           close(((t_client *) elem)->_sock);
                       }), NULL);
        this->_clientSock->freeAll(this->_clientSock,
                                   lambda(void, (void *elem), {
                                       xfree((t_client *) elem,
                                             sizeof(t_client));
                                   }));
        this->_clientSock->Free(this->_clientSock);
    }
    shutdown(this->_sock, 2);
    close(this->_sock);
    xfree(this, sizeof(Network));
}