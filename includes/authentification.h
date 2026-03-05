/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** authentification
*/

#ifndef AUTHENTICATION_H
    #define AUTHENTICATION_H

    #include "myftp.h"

int authenticate_user(client_session_t *session, const char *username,
    const char *password);
int handle_user_command(client_session_t *session, char *args);
int handle_pass_command(client_session_t *session, char *args);

    #define AUTH_ANONYMOUS "Anonymous"
    #define AUTH_SUCCESS 0
    #define AUTH_FAILURE -1

#endif /* !AUTHENTICATION_H */
