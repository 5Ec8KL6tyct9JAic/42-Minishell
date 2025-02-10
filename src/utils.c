/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:01:43 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Libère la mémoire allouée pour un tableau d'arguments
** @param args: tableau à libérer
*/
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (args[i])
			free(args[i]);
		i++;
	}
	free(args);
}

/*
** Compare deux chaînes de caractères
** @param s1: première chaîne
** @param s2: deuxième chaîne
** @return: différence entre les caractères différents ou 0 si identiques
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	sig_save_handler(int new)
{
	static int	old;

	if (old == new)
		return (old);
	old = new;
	return (old);
}

/*
** Vérifie si un caractère est un espace (whitespace)
** @param c: caractère à vérifier
** @return: 1 si c'est un espace, 0 sinon
*/
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
		c == '\v' || c == '\f' || c == '\r');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}