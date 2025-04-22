#include "minishell.h"

int	init_env(char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data(NULL);
	while (env[i])
		i++;
	if (ft_calloc((void **)&(data->env), i + 1, sizeof(char *)))
		return (1);
	while (i--)
	{
		if (ft_strdup(data->env + i, env[i]))
			return (1);
	}
	return (0);
}

int	add_env(char *str)
{
	char	*res;
	t_data	*data;
	int		len;
	int		y;

	y = 0;
	data = get_data(NULL);
	if (is_current_env(str))
		return (0);
	len = get_len(data->env) + 1;
	if (ft_realloc((void **)&data->env,
			sizeof(char *) * len,
			sizeof(char *) * (len + 1)))
		return (1);
	while (str[y] && str[y] != '=')
		y++;
	if (!str[y])
		ft_strjoin(&res, str, "=");
	else
		res = str;
	if (ft_strdup(data->env + len - 1, res))
		return (1);
	if (!str[y])
		del_malloc(res);
	return (0);
}

int	del_env(char *str)
{
	t_data	*data;
	char	**last;
	int		pos_del;
	int		i;
	int		y;

	i = 0;
	y = -1;
	data = get_data(NULL);
	pos_del = get_pos_del(ft_strlen(str), str);
	if (!data->env[pos_del])
		return (1);
	last = data->env;
	if (ft_calloc((void **)&data->env, sizeof(char *), get_len(data->env)))
		return (1);
	while (last[++y])
	{
		if (y != pos_del)
			data->env[i++] = last[y];
	}
	data->env[i] = NULL;
	return (del_malloc((void *)last));
}

int	get_env(char **res, char *name)
{
	char	*pos;
	char	**current;
	t_data	*data;
	size_t	len;

	len = ft_strlen(name);
	data = get_data(NULL);
	current = data->env;
	while (*current)
	{
		if (!ft_strncmp(*current, name, len)
			&& (*current)[len] == '=')
		{
			if (ft_strchr(&pos, *current, '='))
				return (1);
			*res = pos + 1;
			return (0);
		}
		current++;
	}
	return (1);
}
