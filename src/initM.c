/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:26:48 by mehdi             #+#    #+#             */
/*   Updated: 2025/02/03 14:00:02 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(t_cmd *cmd, char *input)
{
	int	i;
	
	i = 0;
    if (input)
        free(input);
	if (!cmd)
		return ;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
    		free(cmd->args[i]);
    		i++;
		}
	}
	free(cmd->input_redirection);
	free(cmd->output_redirection);
	free(cmd);
}

static int handle_redirections(t_cmd *cmd, char **args, int i)
{
    if (ft_strcmp(args[i], "<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
    {
        cmd->input_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], ">") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    else if (ft_strcmp(args[i], ">>") == 0 && args[i + 1])
    {
        cmd->output_redirection = ft_strdup(args[++i]);
        return i;
    }
    return -1;
}

static void cmd_split(t_cmd *cmd, const char *input)
{
    char	**args;
    int		i;
	int		redir_index;
    int		j;

    i = -1;
    j = 0;
    args = ft_split(input);
    cmd->input_redirection = NULL;
    cmd->output_redirection = NULL;
    while (args[++i])
    {
        redir_index = handle_redirections(cmd, args, i);
        if (redir_index != -1)
            i = redir_index;
        else
            cmd->args[j++] = ft_strdup(args[i]);
    }
    cmd->args[j] = NULL;
    i = -1;
    while (args[++i])
        free(args[i]);
    free(args);
}

static int is_bultin(char *cmd)
{
    if (ft_strcmp(cmd, "cd") == 0)
        return (0);
    else if (ft_strcmp(cmd, "echo") == 0)
        return (0);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return (0);
    else if (ft_strcmp(cmd, "export") == 0)
        return (0);
    else if (ft_strcmp(cmd, "unset") == 0)
        return (0);
    else if (ft_strcmp(cmd, "env") == 0)
        return (0);
    else if (ft_strcmp(cmd, "exit") == 0)
        return (0);
    else
        return (1);
}

t_cmd *init_cmd(t_cmd *cmd, const char *input)
{
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
    {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
	cmd->name = NULL;
    cmd->args = malloc(sizeof(char *) * 100);
	if (!cmd->args)
    {
        perror("Erreur d'allocation mémoire pour les arguments");
        exit(EXIT_FAILURE);
    }
    cmd_split(cmd, input);
    cmd->is_builtin = is_bultin(cmd->name);
    return (cmd);
}
