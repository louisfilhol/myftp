/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** socket setup functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include "server.h"
#include "myftp.h"

static int setup_socket_options(int server_socket)
{
    int opt = 1;

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,
        &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        return -1;
    }
    return 0;
}

static int bind_socket(int server_socket, int port)
{
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_socket, (struct sockaddr *)&address,
        sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }
    return 0;
}

static int create_socket(void)
{
    int server_socket;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        perror("socket failed");
        return -1;
    }
    return server_socket;
}

static int setup_socket(int server_socket)
{
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        return -1;
    }
    return 0;
}

int create_server_socket(int port)
{
    int server_socket;

    server_socket = create_socket();
    if (server_socket == -1)
        return -1;
    if (setup_socket_options(server_socket) == -1)
        return -1;
    if (bind_socket(server_socket, port) == -1)
        return -1;
    if (setup_socket(server_socket) == -1)
        return -1;
    return server_socket;
}

int init_server(server_config_t *config)
{
    config->server_socket = create_server_socket(config->port);
    if (config->server_socket == -1)
        return -1;
    return 0;
}
