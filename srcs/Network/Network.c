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

    Log(WARNING, "I'm sure this function is quite useless ! Uncomment if you thinks it's useful");
//    tmp = this->_clientSock->firstElementFromPredicate(
//            this->_clientSock, lambda(bool, (void *elem, void *userData), {
//                if (((t_client *) elem)->_sock == fd)
//                    return (true);
//                else
//                    return (false);
//            }), NULL);
//    if (tmp != NULL) {
//        this->_clientSock->freeThisElem(this->_clientSock,
//                                        lambda(void, (void *data), {
//                                            free((t_client *) data);
//                                        }), tmp);
//    }
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

/*int main(int ac, char **av) {
    Network *net;
    Response *toto;
    Request *req;
    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    if (strcmp(av[1], "server") == 0) {
        net = CreateNetwork(SERVER, 1024, NULL);
        toto = malloc(sizeof(Response));
        toto->destFd = 4;
        toto->message = "Coucou\n";
        while (net->_clientSock->countLinkedList(net->_clientSock) < 3) {
            req = net->Receive(net, &tv);
            if (req != NULL) {
                req->Free(req);
            }
//            if (net->_clientSock->firstElementFromPredicate(net->_clientSock, lambda(bool, (void *param, void *userData), {
//                if (((t_client *) param)->_sock == 4)
//                    return true;
//                else
//                    return false;
//            }), NULL) != NULL)
//                net->Send(toto);
        }
        xfree(toto, sizeof(Response));
        net->DeleteNetwork(net);
    }
    else if (strcmp(av[1], "client") == 0) {
        net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
        while (true) {
            char *buffer = NULL;
            int read;
            size_t len;

            Log(INFORMATION, "Waiting for input");
            if ((read = getline(&buffer, &len, stdin)) != -1) {
                Response *tmp = CreateEmptyResponse();
                tmp->destFd = net->_sock;
                tmp->message = buffer;
                net->Send(tmp);
                req = net->Receive(net, &tv);
                if (req != NULL) {
                    if (req->message && req->message[0] == '-') {
                        req->Free(req);
                        break;
                    }
                    req->Free(req);
                }
            }
        }
        net->DeleteNetwork(net);
    }
//        int i = -1;
//        while (++i < 5) {
//            req = net->Receive(net, 1);
//            if (req != NULL) {
//                if (req->message && req->message[0] == '-') {
//                    req->Free(req);
//                    break;
//                }
//                req->Free(req);
//            }
//            Response *tmp = CreateEmptyResponse();
//            tmp->destFd = net->_sock;
//            tmp->message = strdup("Test !!!\n");
//            net->Send(tmp);
//            tmp->Free(tmp);
//            sleep(1);
//        }
//        net->DeleteNetwork(net);
    return (0);
}

*/