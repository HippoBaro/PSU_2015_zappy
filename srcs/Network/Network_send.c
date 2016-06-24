//
// Created by pasteu_e on 12/06/16.
//

#include "Network.h"

bool Send(Response *rep);

void initNetworkPtrFuncSend(Network *this) {
    this->Send = &Send;
}

bool Send(Response *rep) {
    if (send(rep->destFd, rep->message, strlen(rep->message), 0) !=
        (ssize_t) strlen(rep->message)) {
        Log(WARNING, "Message to socket: %d could not be sent", rep->destFd);
        rep->Free(rep);
        return (false);
    }
    else {
        Log(SUCCESS, "Message to socket: %d have been sent successfully Message was : \"%s\"",
            rep->destFd, rep->message);
        rep->Free(rep);
        return (true);
    }
}