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

    signal(SIGINT, INThandler);
    signal(SIGPIPE, PIPEhandler);
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
                                            free((t_client *) data);
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
                                       free((t_client *) elem);
                                   }));
        this->_clientSock->Free(this->_clientSock);
    }
    shutdown(this->_sock, 2);
    close(this->_sock);
    free(this);
}

/*
int main(int ac, char **av) {
    Network *net;
    Request *req;
    struct timeval tv;


    if (strcmp(av[1], "server") == 0) {
        net = CreateNetwork(SERVER, 1024, NULL);
        while (net->_clientSock->countLinkedList(net->_clientSock) < 3) {
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            req = net->Receive(net, &tv);
            if (req != NULL) {
                req->Free(req);
            }
            if (net->_clientSock->firstElementFromPredicate(net->_clientSock, lambda(bool, (void *param, void *userData), {
                if (((t_client *) param)->_sock == 4)
                    return true;
                else
                    return false;
            }), NULL) != NULL) {
                Response *tmp = CreateEmptyResponse();
                tmp->destFd = 4;
                tmp->message = strdup("Coucou");
                net->Send(tmp);
                //net->Disconnect(net, 4);
            }
        }
        net->DeleteNetwork(net);
    }
    else if (strcmp(av[1], "client") == 0) {
        net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
        while (1) {
//            char *buffer = NULL;
//            ssize_t read;
//            size_t len;
//
//            Log(INFORMATION, "Waiting for input");
//            if ((read = getline(&buffer, &len, stdin)) != -1) {
//                Response *tmp = CreateEmptyResponse();
//                tmp->destFd = net->_sock;
//                tmp->message = buffer;
//                net->Send(tmp);
//            }
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            req = net->Receive(net, &tv);
            if (req != NULL) {
                if (req->message[0] == '-') {
                    req->Free(req);
                    break;
                }
                else
                    Log(INFORMATION, "MSG: %s", req->message);
                req->Free(req);
            }
        }
        net->DeleteNetwork(net);
    }
    return (0);
}
 */