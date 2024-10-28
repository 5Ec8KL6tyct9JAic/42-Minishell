#include "minishell.h"

int	main(void)
{
	char		*input;
	// t_command	*cmd;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		/*cmd = parse_command(input);
		if (cmd->is_builtin)
			execute_builtin(cmd);
		else
			execute_external(cmd);
		free_command(cmd);
		free(input);*/
	}
	return (0);
}