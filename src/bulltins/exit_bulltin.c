/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bulltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:54:34 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/12 15:48:32 by mmouaffa         ###   ########.fr       */
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
        return (handle_error("env", "too many arguments", 2));
    if (!cmd->env || !cmd->env->env)
        exit_with_error("env", "no environment", 1);
    while (cmd->env->env[i])
        ft_putendl_fd(cmd->env->env[i++], STDOUT_FILENO);
    return ;
}

/* check_out_of_range:
 *  Vérifie si un nombre dépasse LONG_MAX ou LONG_MIN.
 */
static bool check_out_of_range(int neg, unsigned long long num, bool *error)
{
    if ((neg == 1 && num > LONG_MAX) || (neg == -1 && num > -(unsigned long)LONG_MIN))
        *error = true;
    return (*error);
}

/* ft_atoi_long:
 *  Convertit une chaîne en long integer.
 */
static int ft_atoi_long(const char *str, bool *error)
{
    unsigned long long num = 0;
    int neg = 1, i = 0;

    while (str[i] && ft_isspace(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
        neg = (str[i++] == '-') ? -1 : 1;
    while (str[i] && ft_isdigit(str[i]))
    {
        num = (num * 10) + (str[i++] - '0');
        if (check_out_of_range(neg, num, error))
            break;
    }
    return (num * neg);
}

/* get_exit_code:
 *  Récupère le code de sortie du builtin exit.
 */
static int get_exit_code(char *arg, bool *error)
{
    unsigned long long i = 0;

    if (!arg)
        return 0;
    while (ft_isspace(arg[i]))
        i++;
    if (arg[i] == '\0' || (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-'))
        *error = true;
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
            *error = true;
        i++;
    }
    i = ft_atoi_long(arg, error);
    return (i % 256);
}

/* exit_builtin:
 *  Exécute la commande builtin exit.
 */
void   exit_builtin(t_cmd *cmd)
{
    int exit_code;
    bool error = false;

    if (!cmd->args || !cmd->args[1])
        exit_code = 0;
    else
    {
        exit_code = get_exit_code(cmd->args[1], &error);
        if (error)
            exit_code = 2;
        else if (cmd->args[2])
            return handle_error("exit", "too many arguments", 1);
    }
    exit(exit_code);
    return ;
}
