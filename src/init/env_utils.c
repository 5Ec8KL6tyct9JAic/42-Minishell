/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:00:00 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 16:03:08 by mmouaffa         ###   ########.fr       */
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

	(*i)++;
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

char	*expand_variables(char *input, t_env *env)
{
	char	*result;
	char	*temp;
	int		i;
	int		start;

	if (!input || !env->env)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			/* Détecter la séquence "$?" */
			if (input[i + 1] && input[i + 1] == '?')
			{
				/* Ajouter la portion avant le "$" */
				if (i > start)
				{
					temp = ft_substr(input, start, i - start);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					{
						char *old = result;
						result = ft_strjoin(result, temp);
						free(old);
					}
					free(temp);
				}
				/* Convertir g_exit_status en chaîne et l'ajouter */
				temp = ft_itoa(g_exit_status);
				if (!temp)
				{
					free(result);
					return (NULL);
				}
				{
					char *old = result;
					result = ft_strjoin(result, temp);
					free(old);
				}
				free(temp);
				i += 2;
				start = i;
				continue;
			}
			/* Cas général pour l'expansion des autres variables */
			/* On suppose que get_env_value gère la lecture de la variable */
			if (input[i + 1] && !ft_isspace(input[i + 1]) &&
				(ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
			{
				/* Ajouter le texte avant le '$' */
				if (i > start)
				{
					temp = ft_substr(input, start, i - start);
					if (!temp)
					{
						free(result);
						return (NULL);
					}
					{
						char *old = result;
						result = ft_strjoin(result, temp);
						free(old);
					}
					free(temp);
				}
				temp = get_env_value(input, &i, env);
				if (!temp)
				{
					free(result);
					return (NULL);
				}
				{
					char *old = result;
					result = ft_strjoin(result, temp);
					free(old);
				}
				free(temp);
				start = i;
				continue;
			}
		}
		i++;
	}
	/* Ajouter la portion restante de la chaîne */
	if (input[start])
	{
		temp = ft_substr(input, start, i - start);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		{
			char *old = result;
			result = ft_strjoin(result, temp);
			free(old);
		}
		free(temp);
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
			if ((cmd->args[i][j + 1] == '$' && !in_single_quote) || (cmd
                ->args[i][j] == '$' && !in_double_quote && !in_single_quote))
			{
				tmp = expand_variables(cmd->args[i], cmd->env);
				if (tmp)
				{
					free(cmd->args[i]);
					cmd->args[i] = tmp;
					break ;
				}
			}
			j++;
		}
		i++;
	}
}
