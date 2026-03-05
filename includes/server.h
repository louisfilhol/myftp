/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** server header
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "myftp.h"
    #include "commands.h"

int create_server_socket(int port);
int init_server(server_config_t *config);
void init_client_session(client_session_t *session,
    int client_socket, const char *home_directory);
void add_client(server_context_t *context, int client_socket);
void remove_client(struct pollfd *fds,
    client_session_t *sessions, int *nfds, int index);
void handle_client_data(struct pollfd *fds,
    client_session_t *sessions, int *nfds, int index);
int run_server(server_config_t *config);

#endif /* !SERVER_H_ */
