#include "minishell.h"

static void	dup_close_out(int tube[2], t_command *command)
{
	close(command->tmp_fd);
	dup2(tube[0], command->tmp_fd);
	close(tube[1]);
	close(tube[0]);
}

static int	concat(char *current, char **res, size_t len, char *end)
{
	char	*tmp;

	if (ft_strncmp(current, end, len + 1) == 0)
		return (1);
	if (ft_strjoin(&tmp, *res, current))
		exit(1);
	del_malloc(*res);
	free(current);
	*res = tmp;
	if (ft_strjoin(&tmp, *res, "\n"))
		exit(1);
	del_malloc(*res);
	*res = tmp;
	return (0);
}

static void	heredoc_fork(char *end, int tube[2])
{
	char	*current;
	char	*res;
	size_t	len;

	current = NULL;
	res = NULL;
	len = ft_strlen(end);
	close(tube[0]);
	while (1)
	{
		current = readline("heredoc>");
		if (concat(current, &res, len, end))
			break ;
	}
	res[ft_strlen(res)] = 0;
	free(current);
	ft_putstr_fd(res, tube[1]);
	del_malloc(res);
	exit(0);
}

int	heredoc(char *end, t_command *command)
{
	int		id;
	int		tube[2];

	pipe(tube);
	id = fork();
	if (!id)
		heredoc_fork(end, tube);
	dup_close_out(tube, command);
	waitpid(id, NULL, 0);
	return (0);
}
