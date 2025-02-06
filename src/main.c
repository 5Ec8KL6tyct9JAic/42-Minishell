/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:20:57 by mmouaffa         ###   ########.fr       */
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
** Point d'entrée principal du programme
** Boucle principale du shell qui :
** 1. Affiche le prompt
** 2. Lit l'entrée utilisateur
** 3. Parse la commande
** 4. Exécute la commande
** 5. Libère la mémoire
*/
int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**args;
	char	***cmds;

	(void)ac;
	(void)av;
	setup_interactive_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (write(1, "exit\n", 5), 0);
		add_history(input);
		args = init_cmd(input);
		free(input);
		if (args && args[0])
		{
			cmds = split_piped_commands(args);
			execute_pipe_commands(cmds);
			free_cmds(cmds);
		}
		free_args(args);
	}
}
