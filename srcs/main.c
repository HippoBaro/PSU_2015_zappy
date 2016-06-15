//
// Created by pasteu_e on 06/06/16.
//

#include "ZappyServer.h"

int main(int ac, char **av) {
    ZappyServer *server = CreateZappyServer();

    server->Configure(server, server->configuration
                    ->ParseFrom(server->configuration, ac, av)
                    ->Validate(server->configuration))
            ->Start(server)
            ->Free(server);
    return 0;
}
