/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bulltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:53:51 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 15:45:39 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* is_n_flag:
 *  Vérifie si un argument est une option -n valide.
 */
static bool is_n_flag(char *arg)
{
    int i = 0;
    bool n_flag = false;

    if (arg[i] != '-')
        return (n_flag);
    i++;
    while (arg[i] && arg[i] == 'n')
        i++;
    if (arg[i] == '\0')
        n_flag = true;
    return (n_flag);
}

/* echo_print_args:
 *  Affiche les arguments donnés sur la sortie standard.
 */
static void echo_print_args(char **args, bool n_flag, int i)
{
    if (!args[i])
    {
        if (!n_flag)
            ft_putchar_fd('\n', STDOUT_FILENO);
        return ;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        else if (!args[i + 1] && !n_flag)
            ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
}

/* echo_builtin:
 *  Exécute la commande builtin echo.
 */
int echo_builtin(t_cmd *cmd)
{
    int i = 1;
    bool n_flag = false;

    while (cmd->args[i] && is_n_flag(cmd->args[i]))
    {
        n_flag = true;
        i++;
    }
    echo_print_args(cmd->args, n_flag, i);
    return (0);
}

/* env_builtin:
 *  Exécute la commande builtin env : Affiche les variables d'environnement.
 */
void    env_builtin(t_cmd *cmd)
{
    int i = 0;

    if (cmd->args && cmd->args[1])
        return handle_error("env", "too many arguments", 2);
    if (!cmd->env || !cmd->env->env)
        exit_with_error("env", "no environment", 1);
    while (cmd->env->env[i])
        ft_putendl_fd(cmd->env->env[i++], STDOUT_FILENO);
    return ;
}
