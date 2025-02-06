/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envM.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:13:56 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:45 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Récupère la valeur d'une variable d'environnement
** @param env: tableau d'environnement
** @param key: clé à rechercher
** @return: valeur de la variable ou NULL si non trouvée
*/
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
        if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
            return (&env[i][key_len + 1]);
    }
    return (NULL);
}

/*
** Met à jour une variable d'environnement existante
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à mettre à jour
** @param new_var: nouvelle valeur complète (key=value)
** @return: 0 si succès, -1 si erreur
*/
int	handle_existing_var(char ***env, const char *key, char *new_var)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], key, ft_strlen(key)) == 0
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

/*
** Met à jour ou ajoute une variable d'environnement
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à définir
** @param value: valeur à associer
** @return: 0 si succès, -1 si erreur
*/
int set_env_var(char ***env, const char *key, const char *value)
{
    int env_size;
    char *new_var;
    char **new_env;

    if (!env || !key || !value || !(new_var = malloc(ft_strlen(key) + ft_strlen(value) + 2)))
        return (-1);
    ft_strcpy(new_var, key);
    ft_strcat(new_var, "=");
    ft_strcat(new_var, value);
    if (update_env_var(env, key, new_var))
        return (0);
    env_size = 0;
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

/*
** Supprime une variable d'environnement
** @param env: pointeur vers le tableau d'environnement
** @param key: clé à supprimer
** @return: 0 si succès, -1 si erreur
*/
int unset_env_var(char ***env, const char *key)
{
    int j;
    int i;

    i = 0;
    if (!env || !key)
        return (-1);
    while ((*env)[i++] != NULL)
    {
        if (ft_strncmp((*env)[i], key, ft_strlen(key)) == 0 && (*env)[i][ft_strlen(key)] == '=')
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
