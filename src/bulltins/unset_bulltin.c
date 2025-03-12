/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bulltin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:55:53 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 12:55:59 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

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
int export_builtin(t_cmd *cmd)
{
    int i = 1;
    char **tmp;
    int ret = EXIT_SUCCESS;

    if (!cmd->args[i])
        return env_builtin(cmd);
    while (cmd->args[i])
    {
        if (!is_valid_env_var_key(cmd->args[i]))
        {
            errmsg_cmd("export", cmd->args[i], "not a valid identifier", false);
            ret = EXIT_FAILURE;
        }
        else if (ft_strchr(cmd->args[i], '=') != NULL)
        {
            tmp = get_key_value_pair(cmd->args[i]);
            if (tmp)
            {
                set_env_var(cmd->env, tmp[0], tmp[1]);
                free_str_tab(tmp);
            }
        }
        i++;
    }
    return ret;
}

/* pwd_builtin:
 *  Exécute la commande intégrée pwd et affiche le
 *  chemin du répertoire de travail actuel.
 */
int pwd_builtin(t_cmd *cmd)
{
    char buf[PATH_MAX];
    char *cwd;

    (void)cmd;
    if (cmd->env->env)
    {
        ft_putendl_fd(cmd->env->env, STDOUT_FILENO);
        return (EXIT_SUCCESS);
    }
    cwd = getcwd(buf, PATH_MAX);
    if (cwd)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return (EXIT_SUCCESS);
    }
    errmsg_cmd("pwd", NULL, strerror(errno), errno);
    return (EXIT_FAILURE);
}

/* unset_builtin:
 *  Supprime les variables d'environnement avec les clés données.
 */
int unset_builtin(t_cmd *cmd)
{
    int i = 1;
    int idx;
    int ret = EXIT_SUCCESS;

    while (cmd->args[i])
    {
        if (!is_valid_env_var_key(cmd->args[i]) || ft_strchr(cmd->args[i], '=') != NULL)
        {
            errmsg_cmd("unset", cmd->args[i], "not a valid identifier", false);
            ret = EXIT_FAILURE;
        }
        else
        {
            idx = get_env_var_index(cmd->env, cmd->args[i]);
            if (idx != -1)
                remove_env_var(cmd->env, idx);
        }
        i++;
    }
    return ret;
}
