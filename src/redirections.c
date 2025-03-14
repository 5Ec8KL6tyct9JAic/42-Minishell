/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:31:02 by davvaler          #+#    #+#             */
/*   Updated: 2025/03/11 21:59:29 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file(char *filename, char *mode, t_cmd *cmd)
{
	if (ft_strcmp(mode, ">") == 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (ft_strcmp(mode, ">>") == 0)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (ft_strcmp(mode, "<") == 0)
		return (open(filename, O_RDONLY));
	cmd->env->exit_status = 1;
	return (-1);
}

static int	handle_redirection(int i, int *in_fd, int *out_fd, t_cmd *cmd)
{
	int	fd;

	if (!cmd->args[i + 1])
		return (print_error("syntax", "missing file for redirection"), -1);
	fd = open_file(cmd->args[i + 1], cmd->args[i], cmd);
	if (fd == -1)
	{
		print_error("minishell", ft_strjoin(cmd->args[i + 1],
				": failed to open file"));
		cmd->env->exit_status = 1;
		return (-1);
	}
	if (cmd->args[i][0] == '<')
		*in_fd = fd;
	else
		*out_fd = fd;
	free(cmd->args[i]);
	free(cmd->args[i + 1]);
	cmd->args[i] = NULL;
	cmd->args[i + 1] = NULL;
	return (0);
}

int	parse_redirections_exec(int *input_fd, int *output_fd, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], ">") || !ft_strcmp(cmd->args[i], ">>")
			|| !ft_strcmp(cmd->args[i], "<"))
		{
			if (handle_redirection(i, input_fd, output_fd, cmd) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

static char	**clean_args(char **args)
{
	char	**new_args;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = -1;
	while (args[++i])
		if (args[i] != NULL && ft_strcmp(args[i], ">") != 0
			&& ft_strcmp(args[i], ">>") != 0 && ft_strcmp(args[i], "<") != 0)
			count++;
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	i = -1;
	j = 0;
	while (args[++i])
		if (args[i] != NULL && ft_strcmp(args[i], ">") != 0
			&& ft_strcmp(args[i], ">>") != 0 && ft_strcmp(args[i], "<") != 0)
			new_args[j++] = args[i];
	new_args[j] = NULL;
	return (new_args);
}

void	execute_with_redirections(t_cmd *cmd, int prev_fd, int has_next)
{
	int		input_fd = -1;
	int		output_fd = -1;
	char	**args_clean;
	char	*cmd_path;
	pid_t	pid;

	(void)has_next;
	if (parse_redirections_exec(&input_fd, &output_fd, cmd) == -1)
		return ;
	
	// 2. Nettoyage des arguments (supprime les tokens redirection)
	args_clean = clean_args(cmd->args);
	if (!args_clean || !args_clean[0])
		return (free(args_clean));

	// 3. Récupérer le chemin absolu de la commande
	cmd_path = get_path(args_clean[0], cmd->env);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", args_clean[0]);
		free(args_clean);
		cmd->env->exit_status = 127;
		exit(127);
	}

	// 4. Fork du processus pour exécuter la commande
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		free(args_clean);
		return;
	}
	if (pid == 0) // Processus enfant
	{
		restore_default_signals();

		// Redirection des entrées/sorties
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		else if (prev_fd != -1)
			dup2(prev_fd, STDIN_FILENO);
		if (output_fd != -1)
			dup2(output_fd, STDOUT_FILENO);

		// Exécute la commande avec execve
		execve(cmd_path, args_clean, cmd->env->env);
		perror("execve"); // Si execve échoue
		cmd->env->exit_status = 127;
		exit(127);
	}

	// 5. Fermeture des fichiers dans le processus parent
	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
	waitpid(pid, NULL, 0); // Attend la fin du processus enfant

	free(cmd_path);
	free(args_clean);
}

int	has_redirection(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0
			|| ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}
