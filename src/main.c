#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_cmd		*cmd;
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    char *input;
    // t_cmd *cmd;

	while (1)
	{
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
    while (1)
    {
        input = read_input();
        if (!input)
            continue;
        /*cmd = parse_command(input);
        if (!cmd)
        {
            fprintf(stderr, "Erreur : commande invalide\n");
            free(input);
            continue;
        }
		init_cmd(cmd, input);
		exec_cmd(cmd, env);
		free_cmd(cmd);
	}
	clear_history();
	return (0);
        if (cmd->is_builtin)
        {
            if (execute_builtin(cmd) != 0)
                fprintf(stderr, "Erreur lors de l'exécution de la commande built-in: %s\n", cmd->args[0]);
        }
        else
            execute_external(cmd);

        free_command(cmd);*/
        free(input);
    }
    clear_history();
    return 0;
}
