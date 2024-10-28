/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:37:18 by dvalerio          #+#    #+#             */
/*   Updated: 2023/12/26 17:54:45 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(int n_exit)
{
	if (n_exit == ERR_USAGE)
		ft_putstr_fd("Error:pipex infile 'cmd1''cmd2' outfile\n", STDERR_FILENO);
	else if (n_exit == ERR_PIPE)
		ft_putstr_fd("Error: pipe creation failed.\n", STDERR_FILENO);
	else if (n_exit == ERR_FORK)
		ft_putstr_fd("Error: failed to fork child process.\n", STDERR_FILENO);
	else if (n_exit == ERR_CMD_NOT_FOUND)
		ft_putstr_fd("Error: command not found.\n", STDERR_FILENO);
	else if (n_exit == ERR_CMD_EXEC)
		ft_putstr_fd("Error: command execution failed.\n", STDERR_FILENO);
	else if (n_exit == ERR_OPEN_INFILE)
		ft_putstr_fd("Error: opening input file failed.\n", STDERR_FILENO);
	else if (n_exit == ERR_OPEN_OUTFILE)
		ft_putstr_fd("Error: opening output file failed.\n", STDERR_FILENO);
	else
		ft_putstr_fd("Error: an unknown error occurred.\n", STDERR_FILENO);
	exit(n_exit);
}
	// Vous pouvez ajouter plus de conditions d'erreur avec exit_handler.

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env(char *name, char **env)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	if (!name)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_cmd;
	char	*full_cmd;
	int		i;

	i = 0;
	paths = ft_split(get_env("PATH", env), ':');
	if (!cmd || !(paths))
		return (NULL);
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(path_cmd, cmd);
		free(path_cmd);
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

void	close_pipes(int *p_fd)
{
	close(p_fd[0]);
	close(p_fd[1]);
}
