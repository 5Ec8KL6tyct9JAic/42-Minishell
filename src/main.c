/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/09 16:30:42 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Libère la mémoire allouée pour un tableau de commandes
** @param cmds: tableau de commandes à libérer
*/
void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
			free(cmds[i][j++]);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

/*
** Initialise l'environnement du shell
** @param env: environnement système
** @return: structure t_env initialisée
*/
static t_env *init_shell_env(char **env)
{
	t_env *shell_env;

	shell_env = malloc(sizeof(t_env));
	if (!shell_env)
		return (NULL);
	shell_env->env = env;
	shell_env->exit_status = 0;
	return (shell_env);
}

/*
** Exécute une commande simple ou une commande avec pipes
** @param input: ligne de commande parsée
** @param env: environnement du shell
*/
static	void	execute_command_line(char **args, t_env *env)
{
	char	***piped_cmds;
	t_cmd	cmd;

	if (!args || !args[0])
		return ;

	// Si la commande contient des pipes
	if (count_pipes(args) > 0)
	{
		piped_cmds = split_piped_commands(args);
		if (piped_cmds)
		{
			execute_pipe_commands(piped_cmds);
			free_cmds(piped_cmds);
		}
	}
	// Sinon, exécute une commande simple
	else
	{
		init_cmd(&cmd, args[0]);
		if (cmd.is_builtin)
			execute_builtin(&cmd, env->env);
		else
			exec_cmd(&cmd, env->env);
	}
}

/*
** Boucle principale du shell
** @param env: environnement système
** @return: code de sortie du shell
*/
static	int	shell_loop(t_env *env)
{
	char	*input;
	char	**args;

	while (1)
	{
		setup_interactive_signals();
		input = readline("minishell> ");

		// Gestion de EOF (Ctrl+D)
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			return (env->exit_status);
		}

		// Ajoute la commande à l'historique si non vide
		if (*input)
			add_history(input);

		// Parse l'entrée
		args = parse_input(input);
		free(input);

		if (args)
		{
			execute_command_line(args, env);
			free_args(args);
		}
	}
	return (env->exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_env	*shell_env;
	int		exit_status;

	(void)ac;
	(void)av;

	// Initialisation de l'environnement
	shell_env = init_shell_env(env);
	if (!shell_env)
		return (1);

	// Configuration des signaux
	setup_interactive_signals();

	// Boucle principale
	exit_status = shell_loop(shell_env);

	// Nettoyage
	free(shell_env);
	return (exit_status);
}
