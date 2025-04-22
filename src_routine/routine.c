#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	data = (t_data){};
	get_data(&data);
	if (init_env(env))
	{
		free_all();
		return (1);
	}
	minishell();
	free_all();
	return (0);
}
