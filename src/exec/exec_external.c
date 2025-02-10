/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:41 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:12:29 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Gets the full path of a command
** @param cmd_name: command name
** @param env: environment variables
** @return: full path or NULL if not found
*/
static char *get_path(const char *cmd_name, char **env)
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

/*
** Exécute une commande externe avec execve
** @param cmd: structure de commande à exécuter
** @param env: environnement
*/
void    exec_external_cmd(t_cmd *cmd, char **env)
{
	char	*path_to_cmd;

	if (cmd->args && cmd->args[0])
	{
		path_to_cmd = get_path(cmd->args[0], env);
		if (!path_to_cmd)
		{
			handle_error(cmd->args[0], "command not found", ERR_CMD_NOT_FOUND);
			exit(127);
		}
		if (execve(path_to_cmd, cmd->args, env) == -1)
		{
			perror("execve");
			free(path_to_cmd);
			handle_error(cmd->args[0], "execution failed", ERR_EXEC_FAILED);
			exit(126);
		}
		free(path_to_cmd);
	}
	else
		exit(0);
}

/*
** Fonction principale d'exécution des commandes
** @param cmd: structure de commande à exécuter
** @param env: environnement
*/
void	exec_cmd(t_cmd *cmd, char **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return;

	if (cmd->is_builtin)
		execute_builtin(cmd, env);
	else
		exec_external_cmd(cmd, env);

	free_args(cmd->args);
	cmd->args = NULL;
}
