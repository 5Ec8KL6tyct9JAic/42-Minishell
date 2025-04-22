#include "minishell.h"

int	ft_rmv_char(char **buffadr, size_t i)
{
	size_t	x;
	size_t	j;
	size_t	size;
	char	*str;
	char	*tmp;

	ft_strdup(&str, *buffadr);
	size = ft_strlen(str);
	if (ft_calloc((void **)&tmp, size, sizeof(char)))
		return (-1);
	x = 0;
	j = 0;
	while (x < size - 1)
	{
		if (x == i)
		{
			j++;
		}
		tmp[x] = str[j];
		x++;
		j++;
	}
	*buffadr = tmp;
	del_malloc(str);
	return (0);
}

void	ft_perror(char *str)
{
	char	*arg[3];

	if (fork() == 0)
	{
		arg[0] = "say";
		arg[1] = strerror(errno);
		arg[2] = NULL;
		if (execve("/usr/bin/say", arg, NULL) < 0)
			exit(1);
	}
	perror(str);
}
