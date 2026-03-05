/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** client management functions
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

void init_client_session(client_session_t *session, int client_socket,
    const char *home_directory)
{
    session->client_socket = client_socket;
    session->data_socket = -1;
    session->is_authenticated = 0;
    session->username[0] = '\0';
    session->data_port = 0;
    if (home_directory && *home_directory) {
        strncpy(session->current_directory, home_directory,
            sizeof(session->current_directory) - 1);
        session->current_directory
            [sizeof(session->current_directory) - 1] = '\0';
    } else {
        strncpy(session->current_directory, "/",
            sizeof(session->current_directory) - 1);
    }
}

void add_client(server_context_t *context, int client_socket)
{
    if (*(context->nfds) >= MAX_CLIENTS) {
        fprintf(stderr, "Maximum number of clients reached\\n");
        close(client_socket);
        return;
    }
    init_client_session(&context->sessions[*(context->nfds)],
        client_socket, context->home_directory);
    context->fds[*(context->nfds)].fd = client_socket;
    context->fds[*(context->nfds)].events = POLLIN;
    context->fds[*(context->nfds)].revents = 0;
    send_response(&context->sessions[*(context->nfds)],
        220, "Service ready for new user.");
    (*(context->nfds))++;
}

void remove_client(struct pollfd *fds,
    client_session_t *sessions, int *nfds, int index)
{
    close_client_connection(&sessions[index]);
    if (index < (*nfds - 1)) {
        memmove(&fds[index], &fds[index + 1],
            ((*nfds) - index - 1) * sizeof(struct pollfd));
        memmove(&sessions[index], &sessions[index + 1],
            ((*nfds) - index - 1) * sizeof(client_session_t));
    }
    (*nfds)--;
}

void handle_client_data(struct pollfd *fds,
    client_session_t *sessions, int *nfds, int index)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    bytes_read = read(sessions[index].client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) {
        remove_client(fds, sessions, nfds, index);
        return;
    }
    process_buffer(&sessions[index], buffer, bytes_read);
}
