#include "minishell.h"

static void	handle_signal(int sig)
{
	(void)sig;
	write(1, "\n$Minishell> ", 4);
}

static void	init_shell(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	rl_outstream = stderr;
}

int	main(void)
{
	char	*input;
	t_cmd	cmd;

	init_shell();
	while ((input = readline("$Minishell> ")))
	{
		if (*input)
		{
			add_history(input);
			init_cmd(&cmd, input);
			if (!args[0])
				continue ;
			cmd.is_builtin = is_builtin(args[0]);
			exec_cmd(&cmd, environ);
			ft_free_tab(args);
		}
		free(input);
	}
	ft_putstr_fd("exit\n", 1);
	return (0);
}
