/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:34:04 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/14 13:11:28 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i])
		printf("%s\n", env->env[i++]);
}

bool is_valid_env_key(const char *key)
{
    int i;

    if (!key || !key[0] || (!ft_isalpha(key[0]) && key[0] != '_'))
        return false;
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return false;
        i++;
    }
    return true;
}

void execute_export(t_cmd *cmd)
{
    int i;
    char *eq;
    char *key;
    char *value;

    i = 1;
    if (!cmd->args[1])  // Si aucun argument, afficher les variables d'env
        return ;
    while (cmd->args[i])
    {
        eq = strchr(cmd->args[i], '=');
        if (eq)
        {
            *eq = '\0';
            key = cmd->args[i];
            value = eq + 1;
        }
        else
        {
            key = cmd->args[i];
            value = NULL;  // Pas de valeur, on ajoute juste la variable
        }

        if (!is_valid_env_key(key))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", cmd->args[i]);
            g_exit_status = 1;
        }
        else
        {
            if (value)
                set_env_var(cmd->env, key, value);  // Ajout ou mise à jour
            else
                set_env_var(cmd->env, key, NULL);  // Ajouter une variable sans valeur
        }
        i++;
    }
}


void	execute_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
		unsetenv(cmd->args[i++]);
}
