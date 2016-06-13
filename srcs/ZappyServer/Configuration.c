//
// Created by barrauh on 6/13/16.
//

#include <getopt.h>
#include "ZappyServer.h"

static Configuration *ParseFrom(Configuration *config, int ac, char **av) {
    int c;
    int index;

    opterr = 0;
    while ((c = getopt (ac, av, "p:x:y:c:t:n:")) != -1) {
        if (c == 'p')
            config->port = atoi(optarg);
        else if (c == 'x')
            config->worldWidth = atoi(optarg);
        else if (c == 'y')
            config->worldHeight = atoi(optarg);
        else if (c == 'c')
            config->initialClientPerTeam = atoi(optarg);
        else if (c == 't')
            config->temporalDelay = atoi(optarg);
        //todo handle teams
    }

    for (index = optind; index < ac; index++)
        printf ("Non-option argument %s\n", av[index]);
    return config;
}

static Configuration   *Validate(Configuration *config) {
    if (config->initialClientPerTeam < 1)
        Log(ERROR, "Initial per-team available slots must be at least 1.");
    if (config->worldHeight < 4 || config->worldWidth < 4)
        Log(ERROR, "Invalid requested map size. A map should be a least 5x5.");
    if (config->port < 1000)
        Log(ERROR, "Unable to bind socket to requested port number. Sub-1000 ports numbers are protocol-reserved.");
    if (config->port > 65535)
        Log(ERROR, "Illegal port number.");
    //todo validate team names
    //todo validate timeDelay
    return config;
}

void DestroyConfiguration(Configuration *config) {
    config->teamNames->freeAll(config->teamNames, lambda(void, (void *elem), {
        free(elem);
    }));
    config->teamNames->Free(config->teamNames);
    free(config);
}

Configuration *CreateConfiguration() {
    Configuration *ret;

    ret = xmalloc(sizeof(Configuration));
    ret->teamNames = CreateLinkedList();
    ret->Validate = &Validate;
    ret->ParseFrom = &ParseFrom;
    ret->Free = &DestroyConfiguration;
    return ret;
}