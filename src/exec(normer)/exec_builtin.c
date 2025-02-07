/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:58:54 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/07 11:34:19 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Exécute une commande builtin
** @param cmd: structure de commande à exécuter
** @param envp: environnement
*/
void	execute_builtin(t_cmd *cmd, char **envp)
{
	if (!cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		execute_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		execute_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		execute_env(envp);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		execute_export(cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		execute_unset(cmd);
	else
	{
		fprintf(stderr, "Commande interne inconnue : %s\n", cmd->args[0]);
		exit_handler(ERR_CMD_NOT_FOUND);
	}
}

/*
** Change le répertoire courant
** @param cmd: structure de commande contenant le chemin
*/
void	execute_cd(t_cmd *cmd)
{
	char	*target;

	target = cmd->args[1];
	if (!target)
		target = getenv("HOME");
	else if (ft_strcmp(target, "-") == 0)
		target = getenv("OLDPWD");
	if (!target)
	{
		fprintf(stderr, "cd: variable d'environnement manquante\n");
		return ;
	}
	if (chdir(target) != 0)
		perror("cd");
	else
		setenv("OLDPWD", getenv("PWD"), 1);
}

/*
** Quitte le shell avec le code de sortie spécifié
** @param cmd: structure de commande contenant le code de sortie
*/
void	execute_exit(t_cmd *cmd)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	if (cmd->args[1])
	{
		while (cmd->args[1][i])
		{
			if (!ft_isdigit(cmd->args[1][i++]))
			{
				fprintf(stderr, "exit: argument numérique requis\n");
				return ;
			}
		}
		exit_code = ft_atoi(cmd->args[1]) % 256;
	}
	exit(exit_code);
}

void	execute_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[++i])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	execute_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}
