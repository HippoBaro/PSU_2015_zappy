//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

static void createSocket(struct Network *this);

static void serverMode(struct Network *this);

static void clientMode(struct Network *this);

static Request *Receive(struct Network *this, struct timeval *tv);

static void DeleteNetwork(struct Network *this);

static bool Send(struct e_Response *rep);

static void initPtrFunc(Network *this) {
    this->Receive = &Receive;
    this->Send = &Send;
    this->DeleteNetwork = &DeleteNetwork;
}

void INThandler(int sig) {
    shutdown(masterSocket, 2);
    close(masterSocket);
    Log(ERROR, "User interupt ! Be careful some data were not destroyed !");
}

void PIPEhandler(int sig) {
    shutdown(masterSocket, 2);
    close(masterSocket);
    Log(ERROR, "The othe side of the socket have been closed :/");
}


Network *CreateNetwork(NetworkType type, uint16_t port, char *addr) {
    Network *this;

    signal(SIGINT, INThandler);
    signal(SIGPIPE, PIPEhandler);
    this = xmalloc(sizeof(Network));
    initPtrFunc(this);
    this->_type = type;
    this->_port = port;
    this->_addr = addr;
    createSocket(this);
    return (this);
}

static void DeleteNetwork(struct Network *this) {
    if (this->_type == SERVER) {
        this->_clientSock->forEachElements(this->_clientSock, lambda(void, (void *elem, void *userData), {
            shutdown(((t_client *) elem)->_sock, 2);
            close(((t_client *) elem)->_sock);
        }), NULL);
        this->_clientSock->freeAll(this->_clientSock, lambda(void, (void *elem), {
            free((t_client *) elem);
        }));
        this->_clientSock->Free(this->_clientSock);
    }
    shutdown(this->_sock, 2);
    close(this->_sock);
    free(this);
}

static void createSocket(struct Network *this) {
    this->_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sock != -1) {
        masterSocket = this->_sock;
        this->_adressage.sin_addr.s_addr = (this->_type == SERVER ? htonl(INADDR_ANY) : inet_addr(this->_addr));
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

static void serverMode(struct Network *this) {
    int opt;

    opt = 1;
    if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt)) < 0)
        Log(ERROR, "Setsockopt error");
    if (bind(this->_sock, (struct sockaddr *) &this->_adressage, this->_adressageSize) != -1) {
        if (listen(this->_sock, 5) == -1)
            Log(ERROR, "Socket listen error");
    }
    else
        Log(ERROR, "Bind Socket error");
}

static void clientMode(struct Network *this) {
    if (connect(this->_sock, (struct sockaddr *) &this->_adressage, sizeof(this->_adressage)) != -1) {
        Log(SUCCESS, "Connexion à %s sur le port %d\n", inet_ntoa(this->_adressage.sin_addr),
            htons(this->_adressage.sin_port));
    }
    else
        Log(ERROR, "Impossible de se connecter");
}

static void addClientToList(struct Network *this, Request **req) {
    t_client *newClient;

    newClient = xmalloc(sizeof(t_client));
    newClient->_adressageSize = sizeof(newClient->_adressage);
    newClient->_sock = accept(this->_sock, (struct sockaddr *) &newClient->_adressage,
                              &newClient->_adressageSize);
    if (newClient->_sock == -1)
        Log(ERROR, "Accept socket client error");
    else {
        Log(SUCCESS, "Un client se connecte avec la socket %d de %s:%d\n", newClient->_sock,
            inet_ntoa(newClient->_adressage.sin_addr), htons(newClient->_adressage.sin_port));
        this->_clientSock->addElemFront(this->_clientSock, (void *) newClient);
        *req = CreateRequest(NULL, newClient->_sock);
        (*req)->type = NEW_CLIENT;
    }
}

static bool checkServerConnectionAndMessage(void *elem, void *userData) {
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
            Log(INFORMATION, "Host disconnected , ip %s , port %d \n",
                inet_ntoa(((t_client *) elem)->_adressage.sin_addr),
                ntohs(((t_client *) elem)->_adressage.sin_port));
            close(sd);
            return (true);
        }
        else {
            buffer[valread] = '\0';
            Log(INFORMATION, "MSG from client with socket : %d -> %s\n", sd, buffer);
            someData->req = CreateRequest(strdup(buffer), sd);
            someData->req->type = EXISTING_CLIENT;
            return (true);
        }
    }
    return (false);
}

static Request *Receive(struct Network *this, struct timeval *tv) {
    t_dataServer *someData;
    Request *req;
    int sd;
    ssize_t valread;
    char buffer[BUFFSIZE];
    int maxfd;
    t_list *tmp;

    someData = xmalloc(sizeof(t_dataServer));
    someData->net = this;
    someData->req = NULL;
    FD_ZERO(&someData->rfds);
    FD_SET(this->_sock, &someData->rfds);
    maxfd = this->_sock;

    if (this->_type == SERVER)
        this->_clientSock->forEachElements(this->_clientSock, lambda(void, (void *elem, void *userData), {
            sd = ((t_client *) elem)->_sock;
            FD_SET(sd, &someData->rfds);
            if (sd > maxfd)
                maxfd = sd;
        }), NULL);

    if (select(maxfd + 1, &someData->rfds, NULL, NULL, tv) == -1) {
        Log(ERROR, "Select error\n");
        exit(0);
    }

    if (this->_type == SERVER) {
        if (FD_ISSET(this->_sock, &someData->rfds)) {
            addClientToList(this, &req);
            xfree(someData, sizeof(t_dataServer));
            return (req);
        }
        tmp = this->_clientSock->firstElementFromPredicate(this->_clientSock, &checkServerConnectionAndMessage, someData);
        if (tmp != NULL) {
            if (someData->req->message != NULL && someData->req->message[0] == '-')
                this->_clientSock->freeThisElem(this->_clientSock, lambda(void, (void *data), {
                    free((t_client *) data);
                }), tmp);
            req = CreateRequest(strdup(someData->req->message), someData->req->socketFd);
            req->type = someData->req->type;
            someData->req->Free(someData->req);
            xfree(someData, sizeof(t_dataServer));
            return (req);
        }
    }
    else if (this->_type == CLIENT) {
        if (FD_ISSET(this->_sock, &someData->rfds)) {
            if ((valread = read(this->_sock, buffer, 1024)) == 0) {
                Log(WARNING, "Server disconnected");
                close(this->_sock);
                xfree(someData, sizeof(t_dataServer));
                req = CreateRequest(strdup("-"), this->_sock);
                return (req);
            }
            else {
                buffer[valread] = '\0';
                Log(INFORMATION, "MSG From server: %s\n", buffer);
                xfree(someData, sizeof(t_dataServer));
                req = CreateRequest(strdup(buffer), this->_sock);
                return (req);
            }
        }
    }
    xfree(someData, sizeof(t_dataServer));
    return (NULL);
}

static bool Send(struct e_Response *rep) {
    if (send(rep->destFd, rep->message, strlen(rep->message), 0) != (ssize_t) strlen(rep->message)) {
        Log(WARNING, "Message to socket: %d could not be sent", rep->destFd);
        rep->Free(rep);
        return (false);
    }
    else {
        Log(SUCCESS, "Message to socket: %d have been sent successfully", rep->destFd);
        rep->Free(rep);
        return (true);
    }
}

int main(int ac, char **av) {
    Network *net;
    Response *toto;
    Request *req;
    struct timeval *tv;

    tv = xmalloc(sizeof(struct timeval));
    tv->tv_sec = 1;
    tv->tv_usec = 0;

    if (strcmp(av[1], "server") == 0) {
        net = CreateNetwork(SERVER, 1024, NULL);
        toto = malloc(sizeof(Response));
        toto->destFd = 4;
        toto->message = "Coucou\n";
        while (net->_clientSock->countLinkedList(net->_clientSock) < 3) {
            req = net->Receive(net, tv);
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
        xfree(tv, sizeof(struct timeval));
        net->DeleteNetwork(net);
    }
    else if (strcmp(av[1], "client_send") == 0) {
        net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
        while (1) {
            char *buffer = NULL;
            int read;
            size_t len;

            Log(INFORMATION, "Waiting for input");
            if ((read = getline(&buffer, &len, stdin)) != -1) {
                Response *tmp = CreateEmptyResponse();
                tmp->destFd = net->_sock;
                tmp->message = buffer;
                net->Send(tmp);
            }
        }
    }
    else if (strcmp(av[1], "client_listen") == 0) {
        net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
        while (1) {
            req = net->Receive(net, tv);
            if (req != NULL) {
                req->Free(req);
            }
        }
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
//        xfree(tv, sizeof(struct timeval));
//        net->DeleteNetwork(net);
    return (0);
}