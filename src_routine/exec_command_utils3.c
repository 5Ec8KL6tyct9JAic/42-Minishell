#include "minishell.h"

int	exec_pipe(t_command *command,
		t_lexical **lexical, t_lexical *last, int pid_i)
{
	t_data	*data;

	data = get_data(NULL);
	pipe(command->pipe);
	data->pid[pid_i] = fork();
	if (data->pid[pid_i] == -1)
		return (1);
	if (!data->pid[pid_i])
	{
		if ((*lexical)->type == IO
			&& (*lexical)->size == 2 && (*lexical)->content[0] == '<')
			heredoc((*lexical)->next->content, command);
		dup2(command->pipe[1], 1);
		close(command->pipe[1]);
		close(command->pipe[0]);
		exec_this(command, *lexical, last, command->tmp_fd);
		exit(1);
	}
	else
	{
		close(command->tmp_fd);
		command->tmp_fd = command->pipe[0];
		close(command->pipe[1]);
	}
	return (0);
}

int	exec_main(t_command *command,
		t_lexical **lexical, t_lexical *last, int pid_i)
{
	t_data	*data;

	data = get_data(NULL);
	if (!built_in_main(*lexical, command))
	{
		data->pid[pid_i] = fork();
		if (data->pid[pid_i] == -1)
			return (1);
		else if (!data->pid[pid_i])
		{
			if ((*lexical)->type == IO && (*lexical)->size == 2
				&& (*lexical)->content[0] == '<')
				heredoc((*lexical)->next->content, command);
			if (exec_this(command, *lexical, last, command->tmp_fd))
			{
				if (errno)
					ft_perror("Error");
				exit (127);
			}
			exit(0);
		}
	}
	close(command->tmp_fd);
	return (0);
}
