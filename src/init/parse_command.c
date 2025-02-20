/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:40:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/19 18:26:58 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Gère les variables d'environnement
*/
void handle_env_var(const char **input, char **args, int *i, t_env *env)
{
	char *var_name;
	char *var_value;
	char	*start;

	(*input)++;  // Skip $
	start = (char *)input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	
	var_name = ft_strndup(start, *input - start);
	var_value = get_env_var(env, var_name);
	free(var_name);

	if (var_value)
		args[*i] = ft_strdup(var_value);
	else
		args[*i] = ft_strdup("");
	(*i)++;
}

/*
** Gère le parsing des arguments entre guillemets
*/
void	handle_quotes(char *input, t_cmd *cmd, int i)
{
	char	**new_args;
	char	*content;
	int		j;

	if (input[i] == '\'')
    {
        handle_single_quotes(input, cmd, i);
        return ;
    }
	content = handle_double_quotes_content(input, cmd->env);
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
	free(cmd->args);
	cmd->args = new_args;
	if (input[i] == '"')
		i++;
}

/*
** Gère le contenu des guillemets doubles avec expansion des variables
*/
char	*handle_double_quotes_content(char *input, t_env *env)
{
	char	*result;
	int		start;

	start = 0;
	while (input[start] && input[start] != '"')
		start++;
	if (input[start] == '$')
	{
		result = get_env_value(input, &start, env);
		if (input[start] != '"')
		{
			free(result);
			return (ft_strdup(""));
		}
		return (result);
	}
	return (ft_strndup(input, start));
}

void	handle_single_quotes(char *input, t_cmd *cmd, int i)
{
	char	**new_args;
	char	*content;
	int		j;
	int		quote_size;

	quote_size = 0;
	while (input[i + quote_size] && input[i + quote_size] != '\'')
		quote_size++;
	content = ft_substr(input, i + 1, quote_size);
	if (!content)
		return ;
	new_args = ft_realloc(cmd->args, 1);
	if (!new_args)
		return ;
	j = 0;
	while (new_args[j])
		j++;
	new_args[j] = content;
	free(cmd->args);
	cmd->args = new_args;
}

void	parse_command(const char *input, t_cmd *cmd)
{
	int	i;
	int	in_arg;

	i = 0;
	in_arg = 0;
	free(cmd->args);
	cmd->args = malloc(64 * sizeof(char *));
	while (*input)
	{
		if (is_quote(*input))
			handle_quotes((char *)input, cmd, i);
		else
			handle_flags_and_args(&input, cmd->args, &i, &in_arg);
	}
	cmd->args[i] = NULL;
}
