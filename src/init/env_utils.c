/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:00:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/19 17:30:37 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var(t_env *env, const char *var_name)
{
	int i = 0;

	if (!env || !var_name)
		return (NULL);
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], var_name, ft_strlen(var_name)) == 0 && env->env[i]
						[ft_strlen(var_name)] == '=')
			return (&env->env[i][ft_strlen(var_name) + 1]);
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *input, int *i, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		start;

	(*i)++;  // Skip le $
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_substr(input, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = get_env_var(env, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
}

char *expand_variables(char *input, t_env *env)
{
    char *result;
    char *expanded;
    int i;
    
    if (!input || !env->env)
        return (NULL);
        
    i = 0;
    while (input[i])
    {
        if (input[i] == '$' && input[i + 1] && !ft_isspace(input[i + 1]))
        {
            expanded = get_env_value(input, &i, env);
            if (!expanded)
                return (NULL);
            // Concaténer avec le résultat précédent
            result = ft_strjoin(result, expanded);
            free(expanded);
        }
        else
            i++;
    }
    return (result);
}

void expand_env_vars(t_cmd *cmd)
{
	int i;
	int j;
	int in_single_quote;
	int in_double_quote;
	char *tmp;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		in_single_quote = 0;
		in_double_quote = 0;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == '\'')
				in_single_quote = !in_single_quote;
			else if (cmd->args[i][j] == '"')
				in_double_quote = !in_double_quote;
			else if (cmd->args[i][j] == '$' && !in_single_quote)
			{
				tmp = expand_variables(cmd->args[i], cmd->env);
				if (tmp)
				{
					free(cmd->args[i]);
					cmd->args[i] = tmp;
					break;
				}
			}
			j++;
		}
		i++;
	}
}
