/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:50:51 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:50:52 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includers.h"

static int	get_prompt(char buff[MAX_PROMPT])
{
	const char	*content_prompt[25] = {"\xF0\x9F\x94\xA5\x1b[91m ",
		NAME, " \x1b[97m\xF0\x9F\x94\xA5\t\xf0\x9f\x91\x89 ", "\x1b[32m[\x1b[97m "};
	int			i;

	i = 4;
	get_pwd((char **)&content_prompt[i++]);
	ft_strdup((char **)&content_prompt[i++], " \x1b[32m]\x1b[97m");
	if (!get_git((char **)&content_prompt[i + 1]))
	{
		ft_strdup((char **)&content_prompt[i], "\x1b[32m[\x1b[96m ");
		ft_strdup((char **)&content_prompt[i + 2], " \x1b[32m]\x1b[97m");
		i += 3;
	}
	ft_strdup((char **)&content_prompt[i], " $ ");
	i = 0;
	while (content_prompt[i])
	{
		if (ft_strlcat(buff, (char *)content_prompt[i],
				MAX_PROMPT) > MAX_PROMPT)
			return (1);
		del_malloc((char *)content_prompt[i++]);
	}
	return (0);
}

static int	prompt(char **line)
{
	char	buff[MAX_PROMPT];
	char	*current_line;
	t_data	*data;

	data = get_data(NULL);
	while (1)
		if (!data->is_running)
			break ;
	ft_bzero(buff, MAX_PROMPT);
	if (get_prompt(buff))
		return (1);
	current_line = readline(buff);
	if (!current_line)
		return (1);
	if (*current_line)
		add_history(current_line);
	*line = current_line;
	return (0);
}

static void	exit_handler(int sign)
{
	t_data	*data;

	data = get_data(NULL);
	if (sign == SIGINT && !data->is_running)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static int	signal_action(void)
{
	struct termios		termios_p;
	struct sigaction	act_int;
	struct sigaction	act_quit;

	act_int.sa_handler = &exit_handler;
	act_quit.sa_handler = SIG_IGN;
	if (tcgetattr(0, &termios_p) != 0)
		return (1);
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &termios_p) != 0
		|| sigaction(SIGINT, &act_int, NULL) != 0
		|| sigaction(SIGQUIT, &act_quit, NULL) != 0)
		return (1);
	return (0);
}

int	minishell(void)
{
	t_data		*data;
	char		*line;

	if (signal_action())
		return (1);
	data = get_data(NULL);
	while (!prompt(&line))
	{
		if (parser(line) || !data->lexical)
			ft_putstr_fd("Error: Command\n", 2);
		else if (exec_command())
			perror("Error:");
		free(line);
	}
	return (0);
}
