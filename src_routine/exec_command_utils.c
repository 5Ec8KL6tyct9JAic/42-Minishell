#include "minishell.h"

int	wait_process(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	get_path(char **path)
{
	char	**env;

	env = get_data(NULL)->env;
	while (*env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
		{
			*path = ((*env) + 5);
			return (0);
		}
		env++;
	}
	return (1);
}

int	get_cmd(char **command_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**paths;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(command_path, cmd));
	if (get_path(&path) || ft_split(&paths, path, ':'))
		return (1 + (0 * del_malloc(path)));
	while (paths[i])
	{
		if (ft_strjoin(&tmp, paths[i], "/")
			|| ft_strjoin(command_path, tmp, cmd))
			return (1 + 0 * (del_malloc(tmp)
					+ del_malloc(command_path)));
		del_malloc(tmp);
		if (access(*command_path, X_OK) == 0)
			return (!free_split(paths));
		del_malloc(*command_path);
		i++;
	}
	return (free_split(paths));
}

int	get_len_cmd(t_lexical *current)
{
	int	res;

	res = 0;
	if (current->type != PIPE)
		res++;
	while (current)
	{
		if (current->type == PIPE)
			res++;
		current = current->next;
	}
	return (res);
}

t_lexical	*get_last_cmd(t_lexical *current)
{
	while (current->next)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (current);
}
