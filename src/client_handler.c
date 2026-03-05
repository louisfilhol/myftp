/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** client_handler
*/

#include "myftp.h"
#include "commands.h"
#include "client_handler.h"

void process_buffer(client_session_t *session,
    char *buffer, ssize_t bytes_read)
{
    buffer[bytes_read] = '\0';
    if (buffer[bytes_read - 1] == '\n')
        buffer[bytes_read - 1] = '\0';
    if (bytes_read > 1 && buffer[bytes_read - 2] == '\r')
        buffer[bytes_read - 2] = '\0';
    process_client_command(session, buffer);
}

void close_client_connection(client_session_t *session)
{
    close(session->client_socket);
    if (session->data_socket > 0)
        close(session->data_socket);
}

void send_response(client_session_t *session, int code, const char *message)
{
    char response[BUFFER_SIZE];

    snprintf(response, sizeof(response), "%d %s\r\n", code, message);
    write(session->client_socket, response, strlen(response));
}
