//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

void clientMode(struct Network *this) {
    if (connect(this->_sock, (struct sockaddr *) &this->_adressage,
                sizeof(this->_adressage)) != -1) {
        Log(SUCCESS, "Connexion à %s sur le port %d",
            inet_ntoa(this->_adressage.sin_addr),
            htons(this->_adressage.sin_port));
    }
    else
        Log(ERROR, "Impossible de se connecter");
}