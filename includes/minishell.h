#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <curses.h>
#include <term.h>

typedef struct s_command {
	char *name;
	char **args;
	char *input_redirection;
	char *output_redirection;
	int is_builtin;
} t_command;

// Prototypes pour parser.c
t_command   *parse_command(char *input);
char        **split_arguments(char *input);
int         is_builtin_command(const char *command_name);

// Prototypes pour builtin.c
int         execute_builtin(t_command *cmd);
int         execute_cd(char **args);
int         execute_echo(char **args);
int         execute_exit(char **args);

// Prototypes pour process.c
int         execute_external(t_command *cmd);
void        handle_redirections(t_command *cmd);

// Utilitaire pour libérer la structure t_command
void        free_command(t_command *cmd);

#endif