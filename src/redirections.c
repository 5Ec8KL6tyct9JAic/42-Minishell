#include "minishell.h"

static int	open_file(char *filename, char *mode)
{
	if (ft_strcmp(mode, ">") == 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (ft_strcmp(mode, ">>") == 0)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (ft_strcmp(mode, "<") == 0)
		return (open(filename, O_RDONLY));
	return (-1);
}

static int	handle_redirection(char **args, int i, int *in_fd, int *out_fd)
{
	int	fd;

	if (!args[i + 1])
		return (-1);
	fd = open_file(args[i + 1], args[i]);
	if (fd == -1)
		return (perror(args[i + 1]), -1);
	if (args[i][0] == '<')
		*in_fd = fd;
	else
		*out_fd = fd;
	free(args[i]);
	free(args[i + 1]);
	args[i] = NULL;
	args[i + 1] = NULL;
	return (0);
}

int	parse_redirections(char **args, int *input_fd, int *output_fd)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>")
			|| !ft_strcmp(args[i], "<"))
		{
			if (handle_redirection(args, i, input_fd, output_fd) == -1)
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

void	execute_with_redirections(char **args, int prev_fd, int has_next)
{
	(void)has_next;
	int		input_fd;
	int		output_fd;
	char	**args_clean;
	pid_t	pid;

	input_fd = -1;
	output_fd = -1;
	if (parse_redirections(args, &input_fd, &output_fd) == -1)
		return ;
	args_clean = clean_args(args);
	if (!args_clean || !args_clean[0])
		return (free(args_clean));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		restore_default_signals();
		if (input_fd != -1)
			dup2(input_fd, STDIN_FILENO);
		else if (prev_fd != -1)
			dup2(prev_fd, STDIN_FILENO);
		if (output_fd != -1)
			dup2(output_fd, STDOUT_FILENO);
		execvp(args_clean[0], args_clean);
		perror("execvp");
		exit(127);
	}
	if (input_fd != -1)
		close(input_fd);
	if (output_fd != -1)
		close(output_fd);
	waitpid(pid, NULL, 0);
	free(args_clean);
}
