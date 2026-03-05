/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** myftp
*/

#ifndef MYFTP_H
    #define MYFTP_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <fcntl.h>
    #include <errno.h>

    #define MAX_CLIENTS 10000
    #define BUFFER_SIZE 1024
    #define MAX_PATH 256

typedef struct {
    int server_socket;
    int port;
    char *home_directory;
    int max_clients;
} server_config_t;

typedef struct {
    int client_socket;
    int data_socket;
    int is_authenticated;
    char username[50];
    char current_directory[256];
    int data_port;
} client_session_t;

typedef struct {
    struct pollfd *fds;
    client_session_t *sessions;
    int *nfds;
    const char *home_directory;
} server_context_t;

#endif /* !MYFTP_H */
