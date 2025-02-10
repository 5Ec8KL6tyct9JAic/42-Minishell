/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davvaler <davvaler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:52:37 by davvaler          #+#    #+#             */
/*   Updated: 2025/02/10 14:21:59 by davvaler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_error(char *cmd, char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	exit_with_error(char *cmd, char *msg, int exit_code)
{
	print_error(cmd, msg);
	exit(exit_code);
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


