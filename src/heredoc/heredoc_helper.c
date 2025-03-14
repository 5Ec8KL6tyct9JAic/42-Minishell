/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:42:11 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/03/11 21:54:59 by mmouaffa         ###   ########.fr       */
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
		exit_with_error(NULL, "heredoc ne marche pas", 130);
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
		g_exit_status = 130;
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

char	**remove_heredoc_tokens(char **args)
{
	int		i;
	int		j;
	int		count;
	char	**new_args;

	/* Compte le nombre d'arguments sans les tokens heredoc */
	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			i += 2;  /* Ignore le token et son délimiteur */
			continue;
		}
		count++;
		i++;
	}
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	/* Copie les arguments en ignorant les tokens heredoc */
	i = 0;
	j = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			i += 2;
			continue;
		}
		new_args[j++] = ft_strdup(args[i]);
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}
