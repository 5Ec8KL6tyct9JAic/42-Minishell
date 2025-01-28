/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:26:48 by mehdi             #+#    #+#             */
/*   Updated: 2025/01/27 12:04:07 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*init_cmd(t_cmd *cmd, const char *input)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	cmd->is_builtin = is_bultin(input);
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	if (!cmd)
		return ;
	free(cmd->name);
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i]);
		free(cmd->args);
		i++;
	}
	free(cmd->input_redirection);
	free(cmd->output_redirection);
	free(cmd);
}

int is_bultin(char *cmd)
{
    if (strcmp(cmd, "cd") == 0)
        return (0);
    else if (strcmp(cmd, "echo") == 0)
        return (0);
    else if (strcmp(cmd, "pwd") == 0)
        return (0);
    else if (strcmp(cmd, "export") == 0)
        return (0);
    else if (strcmp(cmd, "unset") == 0)
        return (0);
    else if (strcmp(cmd, "env") == 0)
        return (0);
    else if (strcmp(cmd, "exit") == 0)
        return (0);
    else
        return (1);
}
