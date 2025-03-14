/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bulltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:55:04 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 16:14:44 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* get_key_value_pair:
 *  Sépare un argument en une paire clé-valeur pour une variable d'environnement.
 */
static char **get_key_value_pair(char *arg)
{
    char **tmp;
    char *eq_pos;

    eq_pos = ft_strchr(arg, '=');
    tmp = malloc(sizeof(char *) * 3);
    if (!tmp)
        return NULL;
    tmp[0] = ft_substr(arg, 0, eq_pos - arg);
    tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
    tmp[2] = NULL;
    return tmp;
}

/* export_builtin:
 *  Ajoute les variables données aux variables d'environnement.
 */
/* Vérifie si une clé d'environnement est valide */
static bool is_valid_env_key(const char *key)
{
    int i = 0;

    if (!key || (!ft_isalpha(key[i]) && key[i] != '_'))
        return false;
    i++;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return false;
        i++;
    }
    return true;
}

/* export_builtin:
 *  Ajoute les variables données aux variables d'environnement.
 */
void    export_builtin(t_cmd *cmd)
{
    int i = 1;
    char **tmp;

    if (!cmd->args[i])
        return env_bulltin(cmd->env);
    while (cmd->args[i])
    {
        char *eq_pos = ft_strchr(cmd->args[i], '=');
        if (!is_valid_env_key(cmd->args[i]))
        {
            handle_error("export", "not a valid identifier", false);
        }
        else if (eq_pos != NULL)
        {
            tmp = get_key_value_pair(cmd->args[i]);
            if (tmp)
            {
                set_env_var(cmd->env, tmp[0], tmp[1]);
                free_args(tmp);
            }
        }
        i++;
    }
    return ;
}

