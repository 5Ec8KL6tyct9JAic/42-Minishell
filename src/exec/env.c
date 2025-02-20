/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:13:56 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/19 17:33:12 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Met à jour une variable d'environnement existante
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à mettre à jour
** @param new_var: nouvelle valeur complète (key=value)
** @return: 0 si succès, -1 si erreur
*/
int	handle_existing_var(t_env *env, const char *key, char *new_var)
{
	int	i;

	i = -1;
	while (env->env[++i])
	{
		if (ft_strncmp(env->env[i], key, ft_strlen(key)) == 0
			&& env->env[i][ft_strlen(key)] == '=')
		{
			free(env->env[i]);
			env->env[i] = new_var;
			return (0);
		}
	}
	return (-1);
}

/*
** Met à jour ou ajoute une variable d'environnement
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à définir
** @param value: valeur à associer
** @return: 0 si succès, -1 si erreur
*/
int	set_env_var(t_env *env, const char *key, const char *value)
{
	int		env_size;
	char	*new_var;
	char	**new_env;

	new_var = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!env || !key || !value || !(new_var))
		return (-1);
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	if (update_env_var(env, key, new_var))
		return (0);
	env_size = 0;
	while (env->env[env_size])
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	new_env[env_size] = new_var;
	new_env[env_size + 1] = NULL;
	env->env = new_env;
	return (0);
}

/*
** Supprime une variable d'environnement
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à supprimer
** @return: 0 si succès, -1 si erreur
*/
int	unset_env_var(t_env *env, const char *key)
{
	int	j;
	int	i;

	i = 0;
	if (!env || !key)
		return (-1);
	while (env->env[i++] != NULL)
	{
		if (ft_strncmp(env->env[i], key, ft_strlen(key)) == 0 && env->env
			[i][ft_strlen(key)] == '=')
		{
			free(env->env[i]);
			j = i;
			while (env->env[j++] != NULL)
				env->env[j] = env->env[j + 1];
			return (0);
		}
	}
	return (-1);
}

/*
** Updates an existing environment variable
** @param env: pointer to environment array
** @param key: variable name
** @param new_var: new value in format "KEY=VALUE"
** @return: 0 on success, -1 on failure
*/
int    update_env_var(t_env *env, const char *key, char *new_var)
{
    int     i;
    size_t  key_len;

    i = 0;
    key_len = ft_strlen(key);
    while (env->env[i])
    {
        if (ft_strncmp(env->env[i], key, key_len) == 0 && env->env[i][key_len] == '=')
        {
            free(env->env[i]);
            env->env[i] = new_var;
            return (0);
        }
        i++;
    }
    return (-1);
}
