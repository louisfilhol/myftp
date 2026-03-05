/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** server
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
#include "client_handler.h"

static void handle_new_client_connection(server_context_t *context,
    server_config_t *config)
{
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int flags;

    client_socket = accept(config->server_socket,
        (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0)
        return;
    flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);
    add_client(context, client_socket);
}

static void process_client_events(struct pollfd *fds,
    client_session_t *sessions, int *nfds)
{
    int i;

    for (i = 1; i < *nfds; i++) {
        if (fds[i].revents & POLLIN) {
            handle_client_data(fds, sessions, nfds, i);
        }
    }
}

static int handle_server_events(struct pollfd *fds,
    client_session_t *sessions, int *nfds, server_config_t *config)
{
    int poll_count;
    server_context_t context;

    context.fds = fds;
    context.sessions = sessions;
    context.nfds = nfds;
    context.home_directory = config->home_directory;
    poll_count = poll(fds, *nfds, -1);
    if (poll_count < 0) {
        perror("poll");
        return -1;
    }
    if (fds[0].revents & POLLIN) {
        handle_new_client_connection(&context, config);
    }
    process_client_events(fds, sessions, nfds);
    return 0;
}

int run_server(server_config_t *config)
{
    struct pollfd fds[MAX_CLIENTS + 1];
    client_session_t sessions[MAX_CLIENTS];
    int nfds = 1;
    int flags;

    if (init_server(config) != 0) {
        fprintf(stderr, "Failed to initialize server\n");
        return 84;
    }
    printf("Server started on port %d\n", config->port);
    fds[0].fd = config->server_socket;
    fds[0].events = POLLIN;
    flags = fcntl(config->server_socket, F_GETFL, 0);
    fcntl(config->server_socket, F_SETFL, flags | O_NONBLOCK);
    while (1) {
        if (handle_server_events(fds, sessions, &nfds, config) < 0) {
            break;
        }
    }
    return 0;
}
