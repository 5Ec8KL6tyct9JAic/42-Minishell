/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bulltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:56:37 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 16:17:45 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* pwd_builtin:
 *  Exécute la commande intégrée pwd et affiche le
 *  chemin du répertoire de travail actuel.
 */
void    pwd_builtin(t_cmd *cmd)
{
    char buf[PATH_MAX];
    char *cwd;

    (void)cmd;
    if (cmd->env->env)
    {
        ft_putendl_fd(cmd->env->env, STDOUT_FILENO);
        return ;
    }
    cwd = getcwd(buf, PATH_MAX);
    if (cwd)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return ;
    }
    exit_with_error("pwd", strerror(errno), errno);
    return ;
}
