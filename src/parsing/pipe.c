/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/19 17:32:12 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Compte le nombre de pipes dans la commande
** @param args: tableau d'arguments à analyser
** @return: nombre de pipes trouvés
*/
int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

/*
** Divise la commande en sous-commandes séparées par des pipes
** @param args: tableau d'arguments à diviser
** @return: tableau de tableaux contenant les sous-commandes
*/
char	***split_piped_commands(char **args)
{
	int		i;
	int		j;
	int		k;
	int		pipe_count;
	char	***cmds;

	pipe_count = count_pipes(args);
	cmds = malloc(sizeof(char **) * (pipe_count + 2));
	if (!cmds)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		k = 0;
		cmds[j] = malloc(sizeof(char *) * 256);
		while (args[i] && ft_strcmp(args[i], "|") != 0)
			cmds[j][k++] = ft_strdup(args[i++]);
		cmds[j][k] = NULL;
		if (args[i])
			i++;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}
