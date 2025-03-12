/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:16:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 21:49:53 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	handle_exec_error(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		print_error("minishell", ft_strjoin(cmd, ": No such file or directory"));
	else if (access(cmd, X_OK) == -1)
		print_error("minishell", ft_strjoin(cmd, ": Permission denied"));
	else
		print_error("minishell", ft_strjoin(cmd, ": Command not found"));
	exit(127);
}

void	exit_with_error(char *cmd, char *msg, int exit_code)
{
	print_error(cmd, msg);
	exit(exit_code);
}

void	print_error(char *cmd, char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
        g_exit_status = 127;
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
    g_exit_status = 127;
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
