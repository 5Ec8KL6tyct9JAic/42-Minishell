/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bulltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:45:53 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 15:43:30 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* update_wds:
 *  Met à jour les variables PWD et OLDPWD dans l'environnement après un changement de répertoire.
 */
static void update_wds(t_env *env, char *wd)
{
    char *old_pwd = get_env_var(env, "PWD");
    set_env_var(env, "OLDPWD", old_pwd);
    set_env_var(env, "PWD", wd);
    free(wd);
}

/* chdir_errno_mod:
 *  Corrige l'erreur ESTALE en ENOENT sur certains systèmes.
 */
static bool chdir_errno_mod(char *path)
{
    if (errno == ESTALE)
        errno = ENOENT;
    handle_error("cd", path, errno);
    return false;
}

/* change_dir:
 *  Change le répertoire de travail et met à jour OLDPWD.
 */
static bool change_dir(t_cmd *cmd, char *path)
{
    char cwd[PATH_MAX];
    char *ret;
    char *tmp;

    if (chdir(path) != 0)
        return chdir_errno_mod(path);
    
    ret = getcwd(cwd, PATH_MAX);
    if (!ret)
    {
        handle_error("cd: error retrieving current directory",
            "getcwd: cannot access parent directories", errno);
        tmp = get_env_var(cmd->env, "PWD");
        if (!tmp)
            return false;
        ret = ft_strjoin(tmp, "/");
        tmp = ret;
        ret = ft_strjoin(ret, path);
        free(tmp);
    }
    else
        ret = ft_strdup(cwd);
    
    update_wds(cmd->env, ret);
    free(ret);
    return true;
}

/* cd_builtin:
 *  Implémente la commande builtin cd.
 */
void    cd_builtin(t_cmd *cmd)
{
    char *path = NULL;

    if (!cmd->args[1] || ft_isspace(cmd->args[1][0]) || cmd->args[1][0] == '\0' || ft_strncmp(cmd->args[1], "--", 3) == 0)
    {
        path = get_env_var(cmd->env, "HOME");
        if (!path || *path == '\0' || ft_isspace(*path))
            return (handle_error("cd", NULL, EXIT_FAILURE));
        change_dir(cmd, path);
        return ;
    }
    if (cmd->args[2])
        return (handle_error("cd", NULL, EXIT_FAILURE));
    if (ft_strncmp(cmd->args[1], "-", 2) == 0)
    {
        path = get_env_var(cmd->env, "OLDPWD");
        if (!path)
            return (handle_error("cd", NULL, EXIT_FAILURE));
        change_dir(cmd, path);
        return ;
    }
    change_dir(cmd, path);
    return ;
}

