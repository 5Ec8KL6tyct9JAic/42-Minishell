/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 05:01:51 by davvaler         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**args;
	char	*input_redirection;
	char	*output_redirection;
	int		is_builtin;
}			t_cmd;

// init la struct cmd
t_cmd		*init_cmd(t_cmd *cmd, const char *input);
void		free_cmd(t_cmd *cmd);

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
int			execute_builtin(t_cmd *cmd);

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
void	setup_interactive_signals(void);
void	setup_execution_signals(void);
void	restore_default_signals(void);

// execution.c
int		execute_command(char **args);
void	wait_for_child(pid_t pid);

// exec pipe
void	execute_pipe_commands(char ***cmds);

// parser
int	count_pipes(char **args);
char	***split_piped_commands(char **args);

// utils
void	free_args(char **args);
int	ft_strcmp(const char *s1, const char *s2);

// redirections
void	execute_with_redirections(char **args, int prev_fd, int has_next);
int	parse_redirections(char **args, int *input_fd, int *output_fd);

#endif