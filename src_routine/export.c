#include "minishell.h"

int	print_env(void)
{
	char	**env;
	t_data	*data;
	int		i;

	data = get_data(NULL);
	env = data->env;
	while (*env)
	{
		i = 0;
		while ((*env)[i] && (*env)[i] != '=')
			i++;
		if ((*env)[i + 1] != '\0')
		{
			ft_putstr_fd(*env, 1);
			ft_putstr_fd("\n", 1);
		}
		env++;
	}
	return (0);
}

int	print_export(void)
{
	int		i;
	int		len;
	char	**real_env;
	char	**new_env;

	real_env = get_data(NULL)->env;
	len = get_len(real_env);
	if (ft_calloc((void **)&new_env, sizeof(char *), len))
		return (1);
	ft_memcpy((void *)new_env, (void *)real_env, sizeof(char **) * len);
	quicksort(new_env, 0, len - 1);
	i = 0;
	while (i < len)
	{
		printf("%s\n", new_env[i]);
		i++;
	}
	del_malloc(new_env);
	return (0);
}

int	export_cmd(t_command *command)
{
	char	**env;

	env = command->arguments;
	env++;
	if (!*env)
		return (print_export());
	while (*env)
		add_env(*(env++));
	return (0);
}
