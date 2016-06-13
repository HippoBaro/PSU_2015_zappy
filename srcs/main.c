//
// Created by pasteu_e on 06/06/16.
//

#include <Drone.h>
#include <assert.h>
#include "ZappyServer.h"

// JUST A MAIN TEST FOR THE LINKEDLIST MODULE

int main(int ac, char **av) {
    ZappyServer *server = CreateZappyServer();
    Configuration *config = CreateConfiguration();

    config->ParseFrom(config, ac, av)->Validate(config);
    server->Configure(server, config)->Start(server)->Free(server);
    return 0;
}
