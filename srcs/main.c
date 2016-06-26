//
// Created by pasteu_e on 06/06/16.
//

#include <Drone.h>
#include "ZappyServer.h"

#if CLIENT

int main(int ac, char **av) {
    Network *net;
    Request *req;
    struct timeval tv;

    net = CreateNetwork(CLIENT, 1024, "127.0.0.1");
    while (true) {
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

//int main() {
//    Team *team = CreateTeamFrom("hello", 5);
//    Map *world = CreateMap(NULL, 10, 10);
//    Drone *drone1 = CreateDrone(team);
//    Drone *drone2 = CreateDrone(team);
//    MapTile *tile;
//
//    world->AddDrone(world->GetTile(world, 4, 2), drone1);
//    world->AddDrone(world->GetTile(world, 3, 7), drone2);
//
//    /*world->AddDrone(world->GetTile(world, 1, 1), drone1);
//    world->AddDrone(world->GetTile(world, 8, 8), drone2);*/ //OK
//
//    tile = world->GetTileReceivingSound(drone1, drone2, world);
//    printf("Tile receving sound : %ix%i\n", tile->X, tile->Y);
//    return (0);
//}

#endif
