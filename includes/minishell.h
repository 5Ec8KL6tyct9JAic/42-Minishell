#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>

# define ERR_USAGE 1
# define ERR_PIPE 2
# define ERR_FORK 3
# define ERR_CMD_NOT_FOUND 130
# define ERR_CMD_EXEC 5
# define ERR_OPEN_INFILE 6
# define ERR_OPEN_OUTFILE 7

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

// Utilitaire pour liberer la structure t_command
void        free_command(t_command *cmd);

// Pipex

void	exit_handler(int exit);
void	ft_free_tab(char **tab);
char	*get_env(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	close_pipes(int *p_fd);
int		open_file(char *file, int in_or_out);
void	exec(char *cmd, char **env);
void	first_pipe(char **av, int *p_fd, char **env);
void	second_pipe(char **av, int *p_fd, char **env);
int		main(int ac, char **av, char **env);

#endif