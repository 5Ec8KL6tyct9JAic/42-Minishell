/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:41 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 16:03:02 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Gets the full path of a command
** @param cmd_name: command name
** @param env: environment variables
** @return: full path or NULL if not found
*/
char *get_path(const char *cmd_name, t_env *env)
{
	char    *path_env;
	char    **paths;
	char    *full_path;
	int     i;

	path_env = get_env_var(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		char *tmp = full_path;
		full_path = ft_strjoin(full_path, cmd_name);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_args(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_args(paths);
	return (NULL);
}

void	exec_external_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	/* Assure-toi que cmd->path contient le chemin absolu du binaire */
	if (!cmd->path)
	{
		cmd->path = get_cmd_path(cmd->args[0]);
		if (!cmd->path)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd->args[0], 2);
			g_exit_status = 127;  // Code classique pour commande introuvable
			env->exit_status = g_exit_status;
			return ;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		/* Redirection de stdin si heredoc est configuré */
		if (cmd->input_fd != STDIN_FILENO)
		{
			dup2(cmd->input_fd, STDIN_FILENO);
			close(cmd->input_fd);
		}
		execve(cmd->path, cmd->args, env->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 1;  // En cas d'erreur
		env->exit_status = g_exit_status;
	}
	else
	{
		perror("fork");
	}
}
