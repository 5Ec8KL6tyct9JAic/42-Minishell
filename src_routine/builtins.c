/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:50:36 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:50:37 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(char **buff)
{
	if (ft_malloc((void **)buff, 255)
		|| !getcwd(*buff, 255))
		return (1);
	return (0);
}

int	cd_fn(t_command *command)
{
	char	*pwd;
	char	*oldpwd;
	char	*path;

	path = command->arguments[1];
	if (!path)
	{
		if (get_env(&path, "HOME"))
			return (1);
	}
	if (ft_strncmp(path, "-", 1) == 0)
	{
		if (get_env(&path, "OLDPWD"))
			return (1);
	}
	if (get_pwd(&pwd)
		|| ft_strjoin(&oldpwd, "OLDPWD=", pwd)
		|| add_env(oldpwd))
		return (1);
	del_malloc(pwd);
	del_malloc(oldpwd);
	if (chdir((const char *)path) < 0)
		return (1);
	return (0);
}

int	echo_cmd(t_command *command)
{
	int		option;

	option = 0;
	command->arguments++;
	if (!*command->arguments)
		return (0);
	if (ft_strncmp(*command->arguments, "-n", 2) == 0)
	{
		command->arguments++;
		option++;
	}
	while (*command->arguments)
	{
		ft_putstr_fd(*(command->arguments++), 1);
		if (*(command->arguments))
			write(1, " ", 1);
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	unset_cmd(t_command *command)
{
	char	**env;

	env = command->arguments;
	env++;
	while (*env)
		del_env(*(env++));
	return (0);
}
