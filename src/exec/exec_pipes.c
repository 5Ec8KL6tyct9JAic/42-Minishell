/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:24:55 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/06 17:23:07 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gère le processus enfant dans l'exécution des pipes
** @param cmds: tableau des commandes
** @param i: index de la commande actuelle
** @param prev_fd: descripteur de fichier précédent
** @param fd: tableau des descripteurs de fichier du pipe actuel
*/
static void	child_process(char ***cmds, int i, int prev_fd, int fd[2])
{
	if (i > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmds[i + 1])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	execute_with_redirections(cmds[i], prev_fd, cmds[i + 1] != NULL);
	exit(0);
}

/*
** Gère le processus parent dans l'exécution des pipes
** @param pid: PID du processus enfant
** @param prev_fd: pointeur vers le descripteur de fichier précédent
** @param fd: tableau des descripteurs de fichier du pipe actuel
** @param has_next: indique s'il y a une commande suivante
*/
static void	parent_process(pid_t pid, int *prev_fd, int fd[2], int has_next)
{
	waitpid(pid, NULL, 0);
	if (*prev_fd > 0)
		close(*prev_fd);
	if (has_next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}

/*
** Exécute une série de commandes reliées par des pipes
** @param cmds: tableau des commandes à exécuter
*/
void	execute_pipe_commands(char ***cmds)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		prev_fd;

	i = 0;
	prev_fd = 0;
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			child_process(cmds, i, prev_fd, fd);
		else
			parent_process(pid, &prev_fd, fd, cmds[i + 1] != NULL);
		i++;
	}
}
