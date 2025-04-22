#include "minishell.h"

char	*get_name_env(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

int	get_pos_del(size_t size_str, char *str)
{
	int		pos_del;
	t_data	*data;

	data = get_data(NULL);
	pos_del = 0;
	while (data->env[pos_del]
		&& ft_strncmp(data->env[pos_del], str, size_str) != 0
		&& data->env[pos_del][size_str] != '=')
		pos_del++;
	return (pos_del);
}

static char	**get_pos_char(char *name)
{
	t_data		*data;
	char		**current;
	size_t		len;

	data = get_data(NULL);
	len = ft_strlen(name);
	current = data->env;
	while (*current)
	{
		if (!strncmp(*current, name, len)
			&& (*current)[len] == '=')
			break ;
		current++;
	}
	return (current);
}

int	is_current_env(char *str)
{
	char		*name;
	char		**current;
	int			y;
	char		*res;

	name = get_name_env(str);
	current = get_pos_char(name);
	if (*current)
	{
		y = 0;
		while (str[y] && str[y] != '=')
			y++;
		if (!str[y])
			ft_strjoin(&res, str, "=");
		else
			res = str;
		ft_strdup(current, res);
		del_malloc(name);
		if (!str[y])
			del_malloc(res);
		return (1);
	}
	return (del_malloc(name));
}
