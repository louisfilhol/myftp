/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** authentification
*/

#include "myftp.h"
#include "authentification.h"
#include "commands.h"
#include "client_handler.h"

int authenticate_user(client_session_t *session, const char *username,
    const char *password)
{
    (void)password;
    if (strcmp(username, "Anonymous") == 0) {
        session->is_authenticated = 1;
        return AUTH_SUCCESS;
    }
    return AUTH_FAILURE;
}

int handle_user_command(client_session_t *session, char *args)
{
    if (!args) {
        send_response(session, 501, "No username given.");
        return 0;
    }
    strncpy(session->username, args, sizeof(session->username) - 1);
    session->username[sizeof(session->username) - 1] = '\0';
    send_response(session, 331, "User name okay, need password.");
    return 0;
}

int handle_pass_command(client_session_t *session, char *args)
{
    (void)args;
    if (strlen(session->username) == 0) {
        send_response(session, 503, "Login with USER first.");
        return 0;
    }
    if (strcmp(session->username, "Anonymous") == 0) {
        session->is_authenticated = 1;
        send_response(session, 230, "User logged in, proceed.");
    } else {
        send_response(session, 530, "Not logged in.");
    }
    return 0;
}
