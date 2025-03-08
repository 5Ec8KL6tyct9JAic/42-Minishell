/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:30:00 by davvaler          #+#    #+#             */
/*   Updated: 2025/03/08 18:55:19 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_quotes(const char **input, char **args, int *i)
{
	const char	*start;

	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	args[*i] = ft_substr(start, 0, *input - start);
	if (args[*i])
		(*i)++;
}

void	handle_quoted_text(const char **input, char **args, int *i, 
							t_env *env, char quote_type)
{
	const char	*start;
	char		*content;

	start = *input;
	while (**input && **input != quote_type)
		(*input)++;
	content = ft_substr(start, 0, *input - start);
	if (!content)
		return ;
	if (quote_type == '"')
	{
		char	*expanded;

		expanded = expand_variables(content, env);
		free(content);
		content = expanded;
	}
	if (content)
	{
		args[*i] = content;
		(*i)++;
	}
	if (**input == quote_type)
		(*input)++;
}

char	*handle_double_quotes_content(char *input, t_env *env)
{
	int		i;
	char	*content;
	char	*result;

	i = 1;
	while (input[i] && input[i] != '"')
		i++;
	content = ft_substr(input, 1, i - 1);
	if (!content)
		return (NULL);
	result = expand_variables(content, env);
	free(content);
	return (result);
}
