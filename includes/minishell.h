/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:56:33 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:34 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PROMPT 255

# include "includers.h"

struct s_command
{
	char	*command;
	char	**arguments;
	int		pipe[2];
	int		tmp_fd;
};

struct s_data
{
	int			len_cmd;
	pid_t		*pid;
	t_lexical	*lexical;
	t_command	command;
	t_malloc	*garbage;
	char		**env;
	int			status;
	int			is_running;
};

int			heredoc(char *end, t_command *command);
void		safe_exit(void);
int			echo_cmd(t_command *command);
int			get_pwd(char **buff);
int			get_git(char **res);

int			init_env(char **env);
int			add_env(char *str);
int			del_env(char *str);

int			cd_fn(t_command *command);
int			echo_cmd(t_command *command);
int			unset_cmd(t_command *command);
int			export_cmd(t_command *command);
int			print_env(void);
int			get_env(char **res, char *name);

int			minishell(void);
int			exec_command(void);
int			parser(char *str);

void		welcome(void);
void		close_dup_in(int pipe[2], int fd);
void		close_dup_out(int pipe[2], int fd);
int			wait_process(void);
int			get_path(char **path);
int			get_cmd(char **command_path, char *cmd);
int			built_in_main(t_lexical *lexical, t_command *command);
int			built_in_fork(t_command *command);
int			get_len_cmd(t_lexical *current);
t_lexical	*get_last_cmd(t_lexical *current);
int			get_name(char **res, t_lexical *node);
int			get_len_arg(t_lexical *node);
int			get_arg(char ***res, t_lexical *node);
int			exec_pipe(t_command *command, t_lexical **lexical,
				t_lexical *last, int pid_i);
int			exec_main(t_command *command, t_lexical **pLexical,
				t_lexical *last, int pid_i);
int			exec_this(t_command	*command, t_lexical *node,
				t_lexical *last, int tmp_fd);
int			is_current_env(char *str);
char		*get_name_env(char *str);
int			get_pos_del(size_t size_str, char *str);
void		ft_perror(char *str);

#endif
