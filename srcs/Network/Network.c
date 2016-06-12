//
// Created by pasteu_e on 12/06/16.
//

#include <string.h>

int client_mode() {

}

int server_mode() {

}

int main(int ac, char **av) {
    if (strcmp(av[1], "server") == 0) {
        server_mode();
    }
    else if (strcmp(av[1], "client") == 0) {
        client_mode();
    }
    return (0);
}