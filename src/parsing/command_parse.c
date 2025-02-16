/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:52:16 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 14:02:51 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Vérifie si un caractère est un guillemet
** @param c: caractère à vérifier
** @return: 1 si c'est un guillemet, 0 sinon
*/
static	int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/*
** Gère le parsing des arguments entre guillemets
** @param input: pointeur vers la chaîne d'entrée
** @param args: tableau de résultats
** @param i: index dans le tableau de résultats
*/
static	void	handle_quotes(const char **input, char **args, int *i)
{
	char	quote;
	char	*start;

	quote = **input;
	(*input)++;
	start = (char *)*input;
	while (**input && **input != quote)
		(*input)++;
	args[*i] = ft_strndup(start, *input - start);
	(*i)++;
	if (**input)
		(*input)++;
}

/*
** Gère le parsing des flags et arguments normaux
** @param input: pointeur vers la chaîne d'entrée
** @param args: tableau de résultats
** @param i: index dans le tableau de résultats
** @param in_arg: flag indiquant si on est dans un argument
*/
static	void	handle_flags_and_args(const char **input,
											char **args, int *i, int *in_arg)
{
	if (*input[0] == '-' && !*in_arg)
	{
		args[(*i)++] = ft_strdup("-");
		while (**input == '-')
			(*input)++;
	}
	else if (**input == ' ')
	{
		*in_arg = 0;
		(*input)++;
	}
	else
	{
		if (!(*in_arg)++)
			args[*i] = ft_strdup("");
		args[*i] = realloc(args[*i], ft_strlen(args[*i]) + 2);
		ft_strncat(args[*i], *input, 1);
		(*input)++;
	}
}

/*
** Parse une commande complète en arguments
** @param input: chaîne d'entrée à parser
** @param args: pointeur vers le tableau de résultats
*/
void	parse_command(const char *input, char ***args)
{
	int	i;
	int	in_arg;

	i = 0;
	in_arg = 0;
	*args = malloc(64 * sizeof(char *));
	while (*input)
	{
		if (is_quote(*input))
			handle_quotes(&input, *args, &i);
		else
			handle_flags_and_args(&input, *args, &i, &in_arg);
	}
	(*args)[i] = NULL;
}

int	parse_redirections(t_cmd *cmd, char **tokens, int *i, t_env *env)
{
	if (ft_strcmp(tokens[*i], "<<") == 0)
	{
		(*i)++;
		if (!tokens[*i])
		{
			handle_error("minishell", "syntax error", 258);
			return (1);
		}
		cmd->heredoc = malloc(sizeof(t_heredoc));
		if (!cmd->heredoc)
		{
			handle_error("minishell", "malloc error", 1);
			return (1);
		}
		cmd->heredoc->delimiter = ft_strdup(tokens[*i]);
		cmd->heredoc->content = NULL;
		if (handle_heredoc(cmd->heredoc, env))
			return (1);
	}
	return (0);
}
