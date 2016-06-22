//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

void serverMode(struct Network *this) {
    int opt;

    opt = 1;
    if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0)
        Log(ERROR, "Setsockopt error");
    if (bind(this->_sock, (struct sockaddr *) &this->_adressage,
             this->_adressageSize) != -1) {
        if (listen(this->_sock, 5) == -1)
            Log(ERROR, "Socket listen error");
    }
    else
        Log(ERROR, "Bind Socket error");
}