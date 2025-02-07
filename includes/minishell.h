/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/07 12:42:30 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
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

# define ERR_CMD_NOT_FOUND        0
# define ERR_PERMISSION_DENIED    1
# define ERR_NO_SUCH_FILE         2
# define ERR_EXEC_FAILED          3
# define ERR_NUMERIC_ARG_REQUIRED 4
# define ERR_INVALID_VAR          5
# define ERR_CMD_EXEC             6

/*
** Structure pour l'environnement du shell
** @member env: tableau des variables d'environnement
** @member exit_status: code de sortie de la dernière commande
*/
typedef struct s_env
{
	char    **env;           // Variables d'environnement
	int     exit_status;     // Code de sortie
}           t_env;

typedef struct s_cmd
{
	char	**args;
	char	*input_redirection;
	char	*output_redirection;
	char	*path;
	int		is_builtin;
	int		input_fd;
	int		output_fd;
}			t_cmd;

typedef struct s_heredoc
{
	char	*delimiter;
	char	*content;
	int		pipe_fd[2];
}			t_heredoc;

// init la struct cmd
void		init_shell(void);
void		init_cmd(t_cmd *cmd, char *input);
void		free_cmd(t_cmd *cmd);
char		*get_cmd_path(char *cmd);
void		ft_free_tab(char **tab);

// Prototypes pour parser.c
t_cmd		*parse_command(char *input);
char		**ft_split(char const *s, char c);
int			is_builtin_command(const char *command_name);

// Prototype error_handling.c
void		handle_error(const char *context,
				const char *target, int error_code);

// Prototypes pour builtin.c
char		*read_input(void);
void		free_input(char *input);
int			builtin_cd(char **args);
int			builtin_echo(char **args);
int			builtin_pwd(void);

// Prototype env.c
int			unset_env_var(char ***env, const char *key);
int			set_env_var(char ***env, const char *key, const char *value);
int			update_env_var(char ***env, const char *key, char *new_var);
int			handle_existing_var(char ***env, const char *key, char *new_var);
char		*get_env_var(char **env, const char *key);

// Prototype de exec.c
void		exec_cmd(t_cmd *cmd, char **env);
void		execute_builtin(t_cmd *cmd);

// Utilitaire pour liberer la structure t_cmd
void		free_command(t_cmd *cmd);

// Pipex
void		exit_handler(int exit);
// void	ft_free_tab(char **tab);
char		*get_env(char *name, char **env);
char		*get_path(char *cmd, char **env);
void		close_pipes(int *p_fd);
int			open_file(char *file, int in_or_out);
void		exec(char *cmd, char **env);
void		first_pipe(char **av, int *p_fd, char **env);
void		second_pipe(char **av, int *p_fd, char **env);
int			main(int ac, char **av, char **env);

// signals.c
void		setup_interactive_signals(void);
void		setup_execution_signals(void);
void		restore_default_signals(void);

// execution.c
int			execute_command(char **args);
void		wait_for_child(pid_t pid);

// exec pipe
void		execute_pipe_commands(char ***cmds);

// parser
int			count_pipes(char **args);
char		***split_piped_commands(char **args);

// utils
void		free_args(char **args);
int			ft_strcmp(const char *s1, const char *s2);

// redirections
void		execute_with_redirections(char **args, int prev_fd, int has_next);
int			parse_redirections(char **args, int *input_fd, int *output_fd);

// Nouveaux prototypes pour init_helper.c
int         handle_redirections(t_cmd *cmd, char **args, int i);
void        cmd_split(t_cmd *cmd, const char *input);
int         is_builtin(char *cmd);
char        *split_redirection(char *str, int *i);
int         handle_quotes_count(const char *input, int *i, int *in_quotes, 
                char *quote_char);

// Nouveaux prototypes pour initM.c
int         handle_redirections_count(const char *input, int *i);
int         count_tokens(const char *input);
void        handle_quotes_split(const char *input, int *i, char **result, int *j);
void        handle_word_split(const char *input, int *i, char **result, int *j);
char        **advanced_split(const char *input);
void        free_split_args(char **args);
void        init_cmd_args(t_cmd *cmd, const char *input);

// Nouveaux prototypes pour heredoc
int         handle_heredoc(t_heredoc *hdoc, char **env);
void        heredoc_signal_handler(int sig);
int         execute_heredoc(t_cmd *cmd, char *delimiter, char **env);
int         is_delimiter_quoted(char *delimiter, int *quote_type);
char        *clean_delimiter(char *delimiter);
char        *expand_heredoc_line(char *line, char **env, int quote_type);

// Variables globales
extern int  g_exit_status;

#endif