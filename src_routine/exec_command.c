#include "minishell.h"

int	parse_command(t_lexical **lexical, int pid_i)
{
	t_data		*data;
	t_command	*command;
	t_lexical	*last;

	data = get_data(NULL);
	command = &(data->command);
	last = get_last_cmd(*lexical);
	get_name(&command->command, *lexical);
	get_arg(&command->arguments, *lexical);
	if (last->type == PIPE)
	{
		if (exec_pipe(command, lexical, last, pid_i))
			return (1);
	}
	else
	{
		if (exec_main(command, lexical, last, pid_i))
			return (1);
	}
	del_malloc(command->arguments);
	*lexical = last->next;
	return (0);
}

int	exec_command(void)
{
	int			pid_i;
	t_data		*data;
	t_lexical	*lexical;

	pid_i = 0;
	data = get_data(NULL);
	data->command.tmp_fd = dup(0);
	lexical = data->lexical;
	data->len_cmd = get_len_cmd(lexical);
	if (ft_calloc((void **)&data->pid, sizeof(pid_t), data->len_cmd))
		return (1);
	data->is_running = 1;
	while (lexical && *lexical->content)
	{
		if (parse_command(&lexical, data->pid[pid_i++]))
			break ;
	}
	data->status = wait_process();
	data->is_running = 0;
	del_malloc(data->pid);
	return (0);
}
