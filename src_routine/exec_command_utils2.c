#include "minishell.h"

int	get_name(char **res, t_lexical *node)
{
	while (node)
	{
		if (node->type == WORD)
		{
			*res = node->content;
			return (0);
		}
		if (node->type == IO)
			node = node->next;
		if (node)
			node = node->next;
	}
	*res = NULL;
	return (1);
}

int	get_len_arg(t_lexical *node)
{
	int	len;

	len = 0;
	while (node)
	{
		if (node->type == WORD)
		{
			while (node && node->type == WORD)
			{
				len++;
				node = node->next;
			}
			return (len);
		}
		if (node->type == IO)
			node = node->next;
		if (node)
			node = node->next;
	}
	return (0);
}

int	get_arg(char ***res, t_lexical *node)
{
	char	**arg;
	int		i;

	i = 0;
	if (ft_calloc((void **)&arg, sizeof(char *), get_len_arg(node) + 1))
		return (1);
	while (node)
	{
		if (node->type == WORD)
		{
			while (node && node->type == WORD)
			{
				arg[i++] = node->content;
				node = node->next;
			}
			*res = arg;
			return (0);
		}
		if (node->type == IO)
			node = node->next;
		if (node)
			node = node->next;
	}
	*res = NULL;
	return (1);
}
