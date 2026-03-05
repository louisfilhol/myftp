/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** commands
*/

#include <ctype.h>
#include "commands.h"
#include "authentification.h"
#include "client_handler.h"

const command_handler_t command_handlers[] = {
    {"USER", handle_user_command},
    {"PASS", handle_pass_command},
    {"QUIT", handle_quit_command},
    {"PWD", handle_pwd_command},
    {"CDUP", handle_cdup_command},
    {"CWD", handle_cwd_command},
    {"DELE", handle_dele_command},
    {"NOOP", handle_noop_command},
    {"HELP", handle_help_command},
    {"PASV", NULL},
    {"PORT", NULL},
    {"RETR", NULL},
    {"STOR", NULL},
    {"LIST", NULL},
    {NULL, NULL}
};

int process_client_command(client_session_t *session, char *command)
{
    char *cmd = strtok(command, " \r\n");
    char *args = strtok(NULL, "\r\n");
    int i;

    if (!cmd) {
        send_response(session, 500, "Empty command.");
        return 0;
    }
    for (i = 0; cmd[i]; i++)
        cmd[i] = toupper(cmd[i]);
    for (i = 0; command_handlers[i].command != NULL; i++) {
        if (strcmp(cmd, command_handlers[i].command) == 0) {
            return command_handlers[i].handler(session, args);
        }
    }
    send_response(session, 500, "Unknown command.");
    return 0;
}

int handle_quit_command(client_session_t *session, char *args)
{
    (void)args;
    send_response(session, 221, "Goodbye.");
    return 1;
}

int handle_noop_command(client_session_t *session, char *args)
{
    (void)args;
    send_response(session, 200, "Command okay.");
    return 0;
}

int handle_help_command(client_session_t *session, char *args)
{
    (void)args;
    send_response(session, 214, "The following commands are recognized:");
    return 0;
}
