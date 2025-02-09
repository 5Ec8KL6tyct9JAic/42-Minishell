/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:58:59 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/09 16:29:11 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Gère la séparation des mots simples
*/
static	void	handle_word_split(const char *input, int *i,
									char **result, int *j)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '<' && input[*i] != '>')
		(*i)++;
	result[*j] = ft_substr(input, start, *i - start);
	(*j)++;
}

/*
** Compte le nombre de tokens dans la chaîne d'entrée
*/
static	int	count_tokens(const char *input)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = 0;
	while (input[i])
	{
		if (handle_quotes_count(input, &i, &in_quotes, &quote_char))
			continue ;
		if (in_quotes)
		{
			i++;
			continue ;
		}
		if (handle_redirections_count(input, &i))
		{
			count++;
			continue ;
		}
		if (ft_isspace(input[i]))
		{
			while (input[i] && ft_isspace(input[i]))
				i++;
			continue ;
		}
		count++;
		while (input[i] && !ft_isspace(input[i])
			&& input[i] != '<' && input[i] != '>')
			i++;
	}
	return (count);
}

/*
** Divise la chaîne d'entrée en tokens
*/
char	**advanced_split(const char *input)
{
	char	**result;
	int		i;
	int		j;
	char	*redir;

	if (!input || !(result = malloc(sizeof(char *)
				* (count_tokens(input) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '<' || input[i] == '>')
		{
			if ((redir = split_redirection((char *)input, &i)))
			{
				result[j++] = redir;
				i++;
				continue ;
			}
		}
		if (input[i] == '"' || input[i] == '\'')
			handle_quotes_split(input, &i, result, &j);
		else
			handle_word_split(input, &i, result, &j);
	}
	result[j] = NULL;
	return (result);
}
