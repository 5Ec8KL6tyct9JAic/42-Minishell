/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:42:11 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:15:26 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Gestionnaire de signal pour le heredoc
** @param sig: numéro du signal reçu
*/
void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

/*
** Exécute le heredoc
** @param cmd: structure de commande
** @param delimiter: délimiteur du heredoc
** @param env: environnement
** @return: 0 en cas de succès, 1 en cas d'erreur
*/
int	execute_heredoc(t_cmd *cmd, char *delimiter, t_env *env)
{
	t_heredoc	hdoc;
	pid_t		pid;
	int			status;

	hdoc.delimiter = delimiter;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		if (handle_heredoc(&hdoc, env))
			exit(1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) == 130)
	{
		// g_exit_status = 130;
		return (1);
	}
	cmd->input_fd = hdoc.pipe_fd[0];
	return (0);
}

char    *extract_var_name(char *str)
{
    int     i;
    char    *name;

    i = 0;
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    name = ft_strndup(str, i);
    return (name);
}
