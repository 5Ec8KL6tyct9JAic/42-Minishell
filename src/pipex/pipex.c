/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:37:58 by dvalerio          #+#    #+#             */
/*   Updated: 2025/02/06 17:24:42 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Ouvre un fichier avec les permissions appropriées
** @param file: nom du fichier à ouvrir
** @param in_or_out: 0 pour lecture, 1 pour écriture
** @return: descripteur de fichier ou -1 en cas d'erreur
*/
int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0644);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ret == -1)
	{
		printf("pipex: %s: No such file or directory\n", file);
		exit(1);
	}
	return (ret);
}

/*
** Exécute une commande avec son chemin complet
** @param cmd: commande à exécuter
** @param env: environnement
*/
void	exec_cmd(char *cmd, char **env)
{
	char	**cmd_args;
	char	*path_to_cmd;

	cmd_args = ft_split(cmd, ' ');
	path_to_cmd = get_path(cmd_args[0], env);
	if (!(*cmd_args) || !(cmd_args))
		exit_handler(ERR_CMD_NOT_FOUND);
	if (path_to_cmd == NULL)
		exit_handler(ERR_CMD_NOT_FOUND);
	if (execve(path_to_cmd, cmd_args, env) == -1)
		exit_handler(ERR_CMD_EXEC);
	free(path_to_cmd);
	ft_free_tab((cmd_args));
}

/*
** Gère le premier processus du pipe
** @param av: arguments du programme
** @param p_fd: descripteurs de fichier du pipe
** @param env: environnement
*/
void	first_pipe(char **av, int *p_fd, char **env)
{
	int	fd_in;

	fd_in = open_file(av[1], 0);
	if (fd_in < 0)
		exit_handler(ERR_OPEN_INFILE);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	exec_cmd(av[2], env);
}

/*
** Gère le second processus du pipe
** @param av: arguments du programme
** @param p_fd: descripteurs de fichier du pipe
** @param env: environnement
*/
void	second_pipe(char **av, int *p_fd, char **env)
{
	int	fd_out;

	fd_out = open_file(av[4], 1);
	if (fd_out < 0)
		exit(EXIT_FAILURE);
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	exec_cmd(av[3], env);
	close(fd_out);
}

/*
** Point d'entrée principal du programme pipex
** Gère l'exécution de deux commandes reliées par un pipe
*/
int	main(int ac, char **av, char **env)
{
	int		p_fd[2];
	int		fd_out;
	pid_t	pid0;
	pid_t	pid1;

	fd_out = open_file(av[4], 1);
	if (ac != 5)
		exit_handler(1);
	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	pid0 = fork();
	if (pid0 < 0)
		exit(EXIT_FAILURE);
	if (pid0 == 0)
		first_pipe(av, p_fd, env);
	close(p_fd[1]);
	dup2(fd_out, STDOUT_FILENO);
	pid1 = fork();
	if (pid1 < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		second_pipe(av, p_fd, env);
	close_pipes(p_fd);
	close(fd_out);
	return (0);
}
