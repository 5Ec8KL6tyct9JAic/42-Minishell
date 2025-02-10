/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:42:52 by davvaler          #+#    #+#             */
/*   Updated: 2025/02/10 15:17:39 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Attend la fin d'un processus enfant et gère les signaux
** @param pid: PID du processus à attendre
*/
void	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}

/*
** Exécute une commande avec gestion des redirections
** @param args: tableau d'arguments de la commande
** @return: 0 en cas de succès, 1 en cas d'erreur
*/
int	execute_command(char **args)
{
	int		input_fd;
	int		output_fd;
	pid_t	pid;

	input_fd = -1;
	output_fd = -1;
	if (parse_redirections_exec(args, &input_fd, &output_fd) == -1 || !args[0])
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		restore_default_signals();
		execvp(args[0], args);
		handle_exec_error(args[0]);
	}
	setup_execution_signals();
	wait_for_child(pid);
	setup_interactive_signals();
	return (0);
}
