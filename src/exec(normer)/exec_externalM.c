/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_externalM.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:41 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/07 11:35:42 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Exécute une commande externe avec execve
** @param cmd: structure de commande à exécuter
** @param env: environnement
*/
static void	exec_external_cmd(t_cmd *cmd, char **env)
{
	char	*path_to_cmd;

	path_to_cmd = get_path(cmd->args[0], env);
	if (!path_to_cmd)
	{
		exit_handler(ERR_CMD_NOT_FOUND);
		return ;
	}
	if (execve(path_to_cmd, cmd->args, env) == -1)
	{
		perror("execve");
		free(path_to_cmd);
		exit_handler(ERR_CMD_EXEC);
	}
	free(path_to_cmd);
}

/*
** Fonction principale d'exécution des commandes
** @param cmd: structure de commande à exécuter
** @param env: environnement
*/
void	exec_cmd(t_cmd *cmd, char **env)
{
	if (!cmd || !cmd->args)
	{
		exit_handler(ERR_CMD_NOT_FOUND);
		return ;
	}
	if (cmd->is_builtin)
	{
		execute_builtin(cmd);
		return ;
	}
	exec_external_cmd(cmd, env);
	ft_free_tab(cmd->args);
}
