#include "minishell.h"

int	main(void)
{
	char		*input;
	t_cmd		*cmd;

	while (1)
	{
		init_cmd(cmd, input);
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
            add_history(input);
        if (strcmp(input, "exit") == 0)
		{
            free(input);
            break;
        }
		cmd = parse_command(input);
		if (cmd->is_builtin)
			execute_builtin(cmd);
		else
			execute_external(cmd);
		free_command(cmd);
		free(input);
	}
	return (0);
}
