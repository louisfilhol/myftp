/*
** EPITECH PROJECT, 2025
** B-NWP-400-MPL-4-1-myftp-louis.filhol-valantin
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "myftp.h"

typedef struct command_handler {
    const char *command;
    int (*handler)(client_session_t *session, char *args);
} command_handler_t;

int process_client_command(client_session_t *session, char *command);
int handle_quit_command(client_session_t *session, char *args);
int handle_noop_command(client_session_t *session, char *args);
int handle_help_command(client_session_t *session, char *args);
int handle_pwd_command(client_session_t *session, char *args);
int handle_cdup_command(client_session_t *session, char *args);
int handle_cwd_command(client_session_t *session, char *args);
int handle_dele_command(client_session_t *session, char *args);

#endif /* !COMMANDS_H_ */
