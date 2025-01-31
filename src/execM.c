/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execM.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:45:41 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/01/31 11:04:50 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void execute_builtin(t_cmd *cmd)
{
	if (strcmp(cmd->args[0], "cd") == 0)
		execute_cd(cmd);
	else if (strcmp(cmd->args[0], "exit") == 0)
		execute_exit(cmd);
	else if (strcmp(cmd->args[0], "echo") == 0)
		execute_echo(cmd);
	else
	{
		fprintf(stderr, "Commande interne inconnue : %s\n", cmd->args[0]);
		exit_handler(ERR_CMD_NOT_FOUND);
	}
}

void exec_cmd(t_cmd *cmd, char **env)
{
	char **cmd_args;
	char *path_to_cmd;

	if (!cmd || !cmd->args)
	{
		exit_handler(ERR_CMD_NOT_FOUND);
		return;
	}
	cmd_args = cmd->args;
	if (cmd->is_builtin)
	{
		execute_builtin(cmd);
		return ;
	}
	path_to_cmd = get_path(cmd_args[0], env);
	if (!path_to_cmd)
	{
		exit_handler(ERR_CMD_NOT_FOUND);
		return ;
	}
	if (execve(path_to_cmd, cmd_args, env) == -1)
	{
		perror("execve");
		free(path_to_cmd);
		exit_handler(ERR_CMD_EXEC);
	}
	free(path_to_cmd);
	ft_free_tab(cmd_args);
}

static void execute_cd(t_cmd *cmd)
{
	char *target_dir;

	target_dir = cmd->args[1];
	if (target_dir == NULL)
	{
		target_dir = getenv("HOME");
		if (target_dir == NULL)
		{
			fprintf(stderr, "cd: HOME non défini\n");
			return;
		}
	}
	if (chdir(target_dir) != 0)
		perror("cd");
}

static void execute_exit(t_cmd *cmd)
{
	int exit_code;

	exit_code = 0;
	if (cmd->args[1] != NULL)
	{
		for (int i = 0; cmd->args[1][i] != '\0'; i++)
		{
			if (!isdigit(cmd->args[1][i]))
			{
				fprintf(stderr, "exit: argument numérique requis\n");
				return ;
			}
		}
		exit_code = atoi(cmd->args[1]);
	}
	exit(exit_code);
}

static void execute_echo(t_cmd *cmd)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (cmd->args[1] != NULL && strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	while (cmd->args[i] != NULL)
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
	{
		printf("\n");
	}
}
