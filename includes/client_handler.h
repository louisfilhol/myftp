/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** client_handler
*/

#ifndef CLIENT_HANDLER_H_
    #define CLIENT_HANDLER_H_

    #include "myftp.h"

void process_buffer(client_session_t *session,
    char *buffer, ssize_t bytes_read);
void close_client_connection(client_session_t *session);
void handle_client(client_session_t *session);
void send_response(client_session_t *session, int code, const char *message);

#endif /* !CLIENT_HANDLER_H_ */
