/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:51:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:51:01 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_io(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
		return (1);
	return (0);
}

static int	is_pipe(char *str)
{
	return (!ft_strncmp(str, "|", 1));
}

static int	get_word_size(char *str)
{
	int	i;
	int	insq;
	int	indq;

	i = 0;
	insq = 0;
	indq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !insq && !indq)
			insq = 1;
		else if (str[i] == '\'' && insq && !indq)
			insq = 0;
		if ((str[i] == '"') && !indq && !insq)
			indq = 1;
		else if (str[i] == '"' && indq && !insq)
			indq = 0;
		if (str[i] == ' ' && !indq && !insq)
			return (i + 1);
		if ((is_io(str + i) || is_pipe(str + i)) && !insq && !indq)
			return (i);
		i++;
	}
	return ((insq || indq) * (-1) + (!(insq || indq)) * i);
}

static int	is_space(char *str)
{
	int	i;

	i = 0;
	while (!is_pipe(str) || !is_io(str))
	{
		if (str[i] == ' ' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	get_type(t_lexical **type, char *str, int *i)
{
	int	val;

	if (!(str))
		return (lex_add_back(type, 0, 0, NULL));
	else if (is_io(str))
	{
		*i += is_io(str);
		return (lex_add_back(type, IO, is_io(str), \
		ft_substr(str, 0, is_io(str))));
	}
	else if (is_pipe(str))
	{
		*i += 1;
		return (lex_add_back(type, PIPE, 1, ft_substr(str, 0, 1)));
	}
	else if (is_space(str))
	{
		val = get_word_size(str);
		if (val == -1)
			return (1);
		if (lex_add_back(type, WORD, val, ft_substr(str, 0, val)))
			return (1);
		*i += val;
	}
	return (0);
}
