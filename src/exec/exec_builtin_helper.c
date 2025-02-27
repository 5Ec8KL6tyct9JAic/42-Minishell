/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:34:04 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/27 17:39:38 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i])
		printf("%s\n", env->env[i++]);
}

void	execute_export(t_cmd *cmd)
{
	int		i;
	char	*eq;

	i = 1;
	if (!cmd->args[1])
	{
		fprintf(stderr, "export: utilisation incorrecte\n");
		g_exit_status = 1;
		return ;
	}
	while (cmd->args[i])
	{
		eq = strchr(cmd->args[i], '=');
		if (eq)
		{
			*eq = '\0';
			setenv(cmd->args[i], eq + 1, 1);
		}
		i++;
	}
}

void	execute_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
		unsetenv(cmd->args[i++]);
}
