/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "server.h"
#include "myftp.h"

int port_checker(int port)
{
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        return 84;
    }
    return 0;
}

int path_checker(char *path)
{
    struct stat st;

    if (stat(path, &st) == -1 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Invalid directory path\n");
        return 84;
    }
    return 0;
}

static int validate_config(server_config_t *config, char *port_str, char *path)
{
    config->port = atoi(port_str);
    if (port_checker(config->port) == 84)
        return 84;
    if (path_checker(path) == 84)
        return 84;
    config->home_directory = path;
    config->max_clients = MAX_CLIENTS;
    return 0;
}

static int parse_arguments(int argc, char *argv[], server_config_t *config)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s port path\n", argv[0]);
        return 84;
    }
    return validate_config(config, argv[1], argv[2]);
}

int main(int argc, char *argv[])
{
    server_config_t config;
    int result;

    result = parse_arguments(argc, argv, &config);
    if (result != 0)
        return result;
    result = run_server(&config);
    close(config.server_socket);
    return result;
}
