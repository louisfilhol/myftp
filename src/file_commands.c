/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** file_commands
*/

#include "commands.h"
#include "authentification.h"
#include "client_handler.h"

int handle_pwd_command(client_session_t *session, char *args)
{
    char response[BUFFER_SIZE];
    char cwd[BUFFER_SIZE];

    (void)args;
    if (!session->is_authenticated) {
        send_response(session, 530, "Not logged in.");
        return 0;
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        send_response(session, 550, "Failed to get current directory.");
        return 0;
    }
    snprintf(response, sizeof(response),
        "\"%s\" is the current directory.", cwd);
    send_response(session, 257, response);
    return 0;
}

int handle_cdup_command(client_session_t *session, char *args)
{
    char cwd[BUFFER_SIZE];

    (void)args;
    if (!session->is_authenticated) {
        send_response(session, 530, "Not logged in.");
        return 0;
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        send_response(session, 550, "Failed to get current directory.");
        return 0;
    }
    if (chdir("..") != 0) {
        send_response(session, 550, "Failed to change to parent directory.");
        return 0;
    }
    send_response(session, 200, "Command okay.");
    return 0;
}

int handle_cwd_command(client_session_t *session, char *args)
{
    if (!session->is_authenticated) {
        send_response(session, 530, "Not logged in.");
        return 0;
    }
    if (!args || strlen(args) == 0) {
        send_response(session, 550, "Failed to change directory.");
        return 0;
    }
    if (chdir(args) != 0) {
        send_response(session, 550, "Failed to change directory.");
        return 0;
    }
    send_response(session, 250, "Directory successfully changed.");
    return 0;
}

int handle_dele_command(client_session_t *session, char *args)
{
    if (!session->is_authenticated) {
        send_response(session, 530, "Not logged in.");
        return 0;
    }
    if (!args || strlen(args) == 0) {
        send_response(session, 550, "Failed to delete file.");
        return 0;
    }
    if (unlink(args) != 0) {
        send_response(session, 550, "Failed to delete file.");
        return 0;
    }
    send_response(session, 250, "File successfully deleted.");
    return 0;
}
