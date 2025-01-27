/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:26:48 by mehdi             #+#    #+#             */
/*   Updated: 2025/01/20 16:06:58 by mehdi            ###   ########.fr       */
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
	cmd->is_builtin = 0;

	
	
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

static void analyze_input(char **args, t_cmd *cmd)
{
	int	i;
    int is_command_detected;

	is_command_detected = 0;
	i = 0;
    while (args[i++])
	{
        if (!is_command_detected)
		{
            char *cmd_path = find_in_path(args[i]);
            if (cmd_path)
			{
                free(cmd_path);
                is_command_detected = 1;
            }
			else
                printf("'%s' n'est pas une commande, peut-être un argument ou un paramètre.\n", args[i]);
        }
		else
		{
            if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0)
			{
                printf("'%s' est une redirection.\n", args[i]);
            }
			else if (args[i][0] == '-')
			{
                printf("'%s' est une option/paramètre.\n", args[i]);
            }
			else
			{
                printf("'%s' est un argument.\n", args[i]);
            }
        }
    }
}

static char *find_in_path(char *cmd)
{
    char *path_env = getenv("PATH");
    if (!path_env) return NULL;
    char *path = strdup(path_env);
    char *dir = strtok(path, ":");
    while (dir) {
        char *full_path = malloc(strlen(dir) + strlen(cmd) + 2);
        sprintf(full_path, "%s/%s", dir, cmd);

        if (is_executable(full_path)) {
            free(path);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");
    }
    free(path);
    return (NULL);
}
