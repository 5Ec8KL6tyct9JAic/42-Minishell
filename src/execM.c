/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:41 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/01/28 18:05:42 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	**cmd_args;
	char	*path_to_cmd;

    if (!cmd->is_builtin)
        execute_external(cmd);
	cmd_args = cmd->args;
	path_to_cmd = get_path(cmd_args[0], env);
	if (!(*cmd_args) || !(cmd_args))
		exit_handler(ERR_CMD_NOT_FOUND);
	if (path_to_cmd == NULL)
	{
		exit_handler(ERR_CMD_NOT_FOUND);
	}	
	if (execve(path_to_cmd, cmd_args, env) == -1)
		exit_handler(ERR_CMD_EXEC);
	free(path_to_cmd);
	ft_free_tab((cmd_args));
}
