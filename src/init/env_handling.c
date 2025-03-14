/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:30:00 by davvaler          #+#    #+#             */
/*   Updated: 2025/03/11 21:56:27 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_env_var(const char **input, char **args, int *i, t_env *env)
{
	char		*var_name;
	char		*var_value;
	const char	*start;

	(*input)++;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	var_name = ft_substr(start, 0, *input - start);
	if (!var_name)
		return ;
	var_value = get_env_var(env, var_name);
	free(var_name);
	if (var_value)
		args[*i] = ft_strdup(var_value);
	else
		args[*i] = ft_strdup("");
	if (args[*i])
		(*i)++;
}

void	handle_double_quotes(const char **input, char **args, int *i, t_env *env)
{
	const char	*start;
	char		*content;
	char		*expanded;

	start = *input;
	while (**input && **input != '"')
	{
		if (**input == '$' && (*input)[1] && 
			(ft_isalnum((*input)[1]) || (*input)[1] == '_'))
		(*input)++;
	}
	content = ft_substr(start, 0, *input - start);
	if (!content)
		return ;
	expanded = expand_variables(content, env);
	free(content);
	if (expanded)
	{
		args[*i] = expanded;
		(*i)++;
	}
}

void	handle_quotes(char *input, t_cmd *cmd, int i)
{
	char	**new_args;
	char	*content;
	int		j;

	if (input[i] == '\'')
	{
		handle_single_quotes((const char **)&input, cmd->args, &i);
		return ;
	}
	if (input[i] == '"')
	{
		content = handle_double_quotes_content(input + i, cmd->env);
		if (!content)
			return ;
		new_args = ft_realloc(cmd->args, 1);
		if (!new_args)
		{
			free(content);
			return ;
		}
		j = 0;
		while (new_args[j])
			j++;
		new_args[j] = content;
		new_args[j + 1] = NULL;
		free(cmd->args);
		cmd->args = new_args;
	}
}
