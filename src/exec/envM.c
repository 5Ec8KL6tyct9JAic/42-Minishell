/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envM.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:13:56 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/01/31 12:19:49 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_env_var(char **env, const char *key)
{
    int     i;
    size_t  key_len;

    i = 0;
    if (!env || !key)
        return (NULL);
    key_len = ft_strlen(key);
    while (env[i++] != NULL)
    {
        if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (&env[i][key_len + 1]);
    }
    return (NULL);
}

int	handle_existing_var(char ***env, const char *key, char *new_var)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if (strncmp((*env)[i], key, ft_strlen(key)) == 0
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_var;
			return (0);
		}
	}
	return (-1);
}

int update_env_var(char ***env, const char *key, char *new_var)
{
    int i = -1;
    while ((*env)[++i])
        if (strncmp((*env)[i], key, strlen(key)) == 0 && (*env)[i][strlen(key)] == '=')
        {
            free((*env)[i]);
            (*env)[i] = new_var;
            return (1);
        }
    return (0);
}


int set_env_var(char ***env, const char *key, const char *value)
{
    int env_size = 0;
    char *new_var, **new_env;

    if (!env || !key || !value || !(new_var = malloc(strlen(key) + strlen(value) + 2)))
        return (-1);
    strcpy(new_var, key);
    strcat(new_var, "=");
    strcat(new_var, value);
    if (update_env_var(env, key, new_var))
        return (0);
    while ((*env)[env_size])
        env_size++;
    if (!(new_env = realloc(*env, (env_size + 2) * sizeof(char *))))
    {
        free(new_var);
        return (-1);
    }
    new_env[env_size] = new_var;
    new_env[env_size + 1] = NULL;
    *env = new_env;
    return (0);
}

int unset_env_var(char ***env, const char *key)
{
    int j;
    int i;

    i = 0;
    if (!env || !key)
        return (-1);
    while ((*env)[i++] != NULL)
    {
        if (strncmp((*env)[i], key, ft_strlen(key)) == 0 && (*env)[i][ft_strlen(key)] == '=')
        {
            free((*env)[i]);
            j = i;
            while ((*env)[j++] != NULL)
                (*env)[j] = (*env)[j + 1];
            return (0);
        }
    }
    return (-1);
}
