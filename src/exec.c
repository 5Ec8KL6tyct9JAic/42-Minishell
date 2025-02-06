#include "minishell.h"

void	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}

int	execute_command(char **args)
{
	pid_t	pid;
	int		i;
	int input_fd = -1;
	int output_fd = -1;
	if (parse_redirections(args, &input_fd, &output_fd) == -1)
    	return (1);
	if (!args[0])
		return (0);
	printf("Commande exécutée : ");
	i = 0;
	while (args[i])
		printf("[%s] ", args[i++]);
	printf("\n");
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		restore_default_signals();
		execvp(args[0], args);
		perror("execvp");
		exit(127);
	}
	setup_execution_signals();
	wait_for_child(pid);
	setup_interactive_signals();
	return (0);
}
