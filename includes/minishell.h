/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:53:36 by davvaler          #+#    #+#             */
/*   Updated: 2025/02/27 17:48:35 by mmouaffa         ###   ########.fr       */
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

# define DEBUG_MODE 0
# define ERR_CMD_NOT_FOUND        0
# define ERR_PERMISSION_DENIED    1
# define ERR_NO_SUCH_FILE         2
# define ERR_EXEC_FAILED          3
# define ERR_NUMERIC_ARG_REQUIRED 4
# define ERR_INVALID_VAR          5
# define ERR_CMD_EXEC             6
extern int g_exit_status;

/*
** Structure pour l'environnement du shell
** @member env: tableau des variables d'environnement
** @member exit_status: code de sortie de la dernière commande
*/
typedef struct s_env
{
	char	**env;
	int		exit_status;
}	t_env;

typedef struct s_heredoc
{
	char	*delimiter;
	char	*content;
	int		pipe_fd[2];
}			t_heredoc;

typedef struct s_cmd
{
	char		**args;
	char		*options;
	char		*input_redirection;
	char		*output_redirection;
	char		*path;
	t_env		*env;
	int			is_builtin;
	int			input_fd;
	int			output_fd;
	t_heredoc	*heredoc;
}			t_cmd;

// Prototypes pour init.c
void		init_shell(void);
void		init_cmd(t_cmd *cmd, char *input, t_env *env);
void		free_cmd(t_cmd *cmd);
int			is_quote(char input);

// Prototypes pour parse_command.c
void		parse_command(const char *input, t_cmd *cmd);
void		handle_env_var(const char **input, char **args, int *i, t_env *env);
void		handle_quotes(char *input, t_cmd *cmd, int i);
char		*handle_double_quotes_content(char *input, t_env *env);
void 		handle_single_quotes(const char **input, char **args, int *i);
void 		handle_flags_and_args(const char **input, char **args, int *i, int *in_arg);

// Prototypes pour env_utils.c
char		*get_env_var(t_env *env, const char *var_name);
char		*get_env_value(char *input, int *i, t_env *env);
char        *expand_variables(char *line, t_env *env);
void		expand_env_vars(t_cmd *cmd);

// Prototypes pour builtins.c
int			is_builtin(char *cmd);

// Prototypes pour parser.c
int			count_pipes(char **args);
char		***split_piped_commands(char **args);
char		**parse_input(char *input);

// Prototypes pour error_handling.c
void		handle_error(const char *context,
				const char *target, int error_code);

// Prototypes pour env.c
int			handle_existing_var(t_env *env, const char *key, char *new_var);
int			set_env_var(t_env *env, const char *key, const char *value);
int			unset_env_var(t_env *env, const char *key);
int			update_env_var(t_env *env, const char *key, char *new_var);

// Prototypes pour exec.c
void		wait_for_child(pid_t pid);
int			execute_command(char **args);
char 		*get_path(const char *cmd_name, t_env *env);
void    	exec_external_cmd(t_cmd *cmd, t_env *env);
int			has_redirection(char **args);

// Prototypes pour exec_builtin.c
void		execute_builtin(t_cmd *cmd, t_env *env);
void		execute_cd(t_cmd *cmd);
void		execute_exit(t_cmd *cmd);
void		execute_echo(t_cmd *cmd);
void		execute_pwd(void);
void		execute_env(t_env *env);
void		execute_export(t_cmd *cmd);
void		execute_unset(t_cmd *cmd);

// Prototypes pour heredoc.c
int			is_delimiter_quoted(char *delimiter, int *quote_type);
char		*clean_delimiter(char *delimiter);
char		*expand_heredoc_line(char *line, t_env *env, int quote_type);
int			handle_heredoc(t_heredoc *hdoc, t_env *env);
void		heredoc_signal_handler(int sig);
int			execute_heredoc(t_cmd *cmd, char *delimiter, t_env *env);
char		*expand_variables(char *line, t_env *env);
void		init_heredoc(t_cmd *cmd);
char 		**remove_heredoc_tokens(char **args);

// Prototypes pour handlers
int			handle_quotes_count(const char *input, int *i,
				int *in_quotes, char *quote_char);
void		handle_quotes_split(const char *input, int *i,
				char **result, int *j);
int			handle_redirections_count(const char *input, int *i);
int			handle_redirections(char **args, int *input_fd, int *output_fd);
char		*split_redirection(char *str, int *i);

// Prototypes pour split.c
char		**advanced_split(const char *input);

// Prototypes pour pipes.c
void		first_pipe(char **av, int *p_fd, char **env);
void		second_pipe(char **av, int *p_fd, char **env);
void		close_pipes(int *p_fd);
void		execute_pipe_commands(char ***cmds);

// Prototypes pour signals.c
void		sigint_handler(int sig);
void		setup_interactive_signals(void);
void		setup_execution_signals(void);
void		restore_default_signals(void);

// Prototypes pour utils.c
void		free_args(char **args);
char		*get_cmd_path(char *cmd);
int			ft_strcmp(const char *s1, const char *s2);
int			sig_save_handler(int new);
int			ft_isspace(int c);
char 		**ft_realloc(char **args, int size);
char*   	remove_quotes(char* str);

// Add with the other exec prototypes
void		execute_with_redirections(t_cmd *cmd, int prev_fd, int has_next);

// errors
void		print_error(char *cmd, char *msg);
void		exit_with_error(char *cmd, char *msg, int exit_code);
void		handle_exec_error(char *cmd);

// Add this with the other prototypes if not already there
void		print_error(char *context, char *message);

// Add this with the other handler prototypes
int			handle_token_redirections(t_cmd *cmd, char **args, int i);

// Prototypes pour redirections
int     parse_redirections_exec(char **args, int *input_fd, int *output_fd);

#endif