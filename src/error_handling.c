/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:16:48 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static const char *get_error_message(int error_code)
{
    static const char *error_messages[] = {
        "command not found",
        "permission denied",
        "no such file or directory",
        "execution failed",
        "numeric argument required",
        "invalid variable",
        NULL
    };
    if (error_code >= 0 && error_code < 6)
        return (error_messages[error_code]);
    return ("unknown error");
}

void    print_error(char *cmd, char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(msg, 2);
}

void    handle_error(const char *context, const char *target, int error_code)
{
    ft_putstr_fd("minishell: ", 2);
    if (context)
    {
        ft_putstr_fd((char *)context, 2);
        ft_putstr_fd(": ", 2);
    }
    if (target)
        ft_putstr_fd((char *)target, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd((char *)get_error_message(error_code), 2);
    ft_putchar_fd('\n', 2);
}

void    handle_exec_error(char *cmd)
{
    handle_error(cmd, "command not found", ERR_CMD_NOT_FOUND);
    exit(127);
} 