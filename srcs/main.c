//
// Created by pasteu_e on 06/06/16.
//

#include "ZappyServer.h"

#if CLIENT

int main(int ac, char **av) {
    Network *net;
    Request *req;
    struct timeval tv;

    net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
    while (1) {
        char *buffer = NULL;
        ssize_t read;
        size_t len;

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
        Log(INFORMATION, "Waiting for input : ");
        if ((read = getline(&buffer, &len, stdin)) != -1) {
            Response *tmp = CreateEmptyResponse();
            tmp->destFd = net->_sock;
            tmp->message = buffer;
            net->Send(tmp);
        }
    }
    net->DeleteNetwork(net);
    return (0);
}

#else

int main(int ac, char **av) {
    ZappyServer *server = CreateZappyServer();

    server->Configure(server, server->configuration
                    ->ParseFrom(server->configuration, ac, av)
                    ->Validate(server->configuration))
            ->Start(server)
            ->Free(server);

    return EXIT_SUCCESS;
}

#endif
