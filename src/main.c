/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:42:56 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 22:09:28 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_exit_status = 0;

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
	shell_env->exit_status = g_exit_status;
	return (shell_env);
}

/*
** Exécute une commande simple ou une commande avec pipes
** @param input: ligne de commande parsée
** @param env: environnement du shell
*/
static	void	execute_command_line(t_cmd *cmd, t_env *env)
{
	char	***piped_cmds;
	char	**new_args;

	if (!cmd->args || !cmd->args[0])
		return ;
	if (cmd->heredoc && cmd->heredoc->delimiter)
	{
		if (handle_heredoc(cmd->heredoc, env))
			return ;
		/* Redirige l'entrée de la commande vers le pipe heredoc */
		cmd->input_fd = cmd->heredoc->pipe_fd[0];
		/* Retire les tokens heredoc du tableau d'arguments */
		new_args = remove_heredoc_tokens(cmd->args);
		if (!new_args)
			return ;
		free_args(cmd->args); /* Fonction pour libérer correctement l'ancien tableau */
		cmd->args = new_args;
	}
	if (count_pipes(cmd->args) > 0)
	{
		piped_cmds = split_piped_commands(cmd->args);
		if (piped_cmds)
		{
			execute_pipe_commands(piped_cmds, env);
			free_cmds(piped_cmds);
		}
	}
	// Sinon, exécute une commande simple
	else
	{
		if (cmd->is_builtin)
			execute_builtin(cmd, env);
		else
			exec_external_cmd(cmd, env);
	}
}

static void	ft_print_tab(char **ta)
{
	int	i;

	i = 0;
	while (ta[i])
	{
		printf("tab[%d] = %s\n", i, ta[i]);
		i++;
	}
}

/*
** Boucle principale du shell
** @param env: environnement système
** @return: code de sortie du shell
*/
static int	shell_loop(t_env *env, t_cmd *cmd)
{
	char	*input;

	while (1)
	{
		setup_interactive_signals();
		input = readline("minishell> ");
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			return (env->exit_status);
		}
		if (*input)
			add_history(input);
		init_cmd(cmd, input, env);
		free(input);
		if (DEBUG_MODE)
		{
			printf("cmd->args:\n");
			ft_print_tab(cmd->args);
		}
		if (cmd->args)
		{
			if (has_redirection(cmd->args))
				execute_with_redirections(cmd, -1, 0);
			else
				execute_command_line(cmd, cmd->env);
			free_args(cmd->args);
		}
	}
	return (env->exit_status);
}


int	main(int ac, char **av, char **env)
{
	t_env	*shell_env;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	cmd = malloc(sizeof(t_cmd));
	init_cmd(cmd, NULL, NULL);
	shell_env = init_shell_env(env);
	if (!shell_env)
		return (1);

	// Boucle principale
	g_exit_status = shell_loop(shell_env, cmd);

	// Nettoyage
	free(shell_env);
	return (g_exit_status);
}
