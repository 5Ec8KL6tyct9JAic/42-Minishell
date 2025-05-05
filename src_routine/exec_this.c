/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_this.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:50:47 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:50:48 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_out(t_lexical *current, int *tmp_fd)
{
	if (current->size == 1)
		*tmp_fd = open(current->next->content,
				O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		*tmp_fd = open(current->next->content,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (*tmp_fd < 0)
	{
		perror("Error");
		return (1);
	}
	close(1);
	dup2(*tmp_fd, 1);
	close(*tmp_fd);
	return (0);
}

static int	open_file_in(t_lexical *current, int *tmp_fd)
{
	*tmp_fd = open(current->next->content, O_RDONLY);
	if (*tmp_fd < 0)
		return (1);
	close(0);
	dup2(*tmp_fd, 0);
	close(*tmp_fd);
	return (0);
}

int	exec_this_while(t_lexical **current, int *tmp_fd)
{
	if ((*current)->type == IO)
	{
		if ((*current)->content[0] == '>')
		{
			if (open_file_out(*current, tmp_fd))
				return (1);
		}
		else
		{
			if ((*current)->size == 1)
			{
				if (open_file_in(*current, tmp_fd))
					return (1);
			}
		}
	}
	*current = (*current)->next;
	return (0);
}

int	exec_this(t_command	*command, t_lexical *node,
						t_lexical *last, int tmp_fd)
{
	char		*command_path;
	t_lexical	*current;

	current = node;
	dup2(tmp_fd, 0);
	close(tmp_fd);
	while (current != last && current)
		if (exec_this_while(&current, &tmp_fd))
			return (1);
	if (!command->command || built_in_fork(command))
		return (0);
	if (get_cmd(&command_path, command->command))
		return (1);
	if (execve(command_path, command->arguments, get_data(NULL)->env) < 0)
		return (1);
	return (0);
}
