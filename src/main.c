#include "minishell.h"

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
			free(cmds[i][j++]);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**args;
	char	***cmds;

	(void)ac;
	(void)av;
	setup_interactive_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (write(1, "exit\n", 5), 0);
		add_history(input);
		args = init_cmd(input);
		free(input);
		if (args && args[0])
		{
			cmds = split_piped_commands(args);
			execute_pipe_commands(cmds);
			free_cmds(cmds);
		}
		free_args(args);
	}
}
