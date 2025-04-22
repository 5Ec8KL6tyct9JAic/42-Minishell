#include "minishell.h"

void	in_dquote(int *i, char c, int quotes)
{
	if (c == '"' && *i == 0 && !quotes)
		*i += 1;
	else if (c == '"' && *i == 1 && !quotes)
		*i -= 1;
}

void	in_squote(int *i, char c, int quotes)
{
	if (c == '\'' && *i == 0 && !quotes)
		*i += 1;
	else if (c == '\'' && *i == 1 && !quotes)
		*i -= 1;
}

void	is_in_dquote(int *i, char c, int quotes)
{
	if (c == '"' && !quotes)
		*i += 1;
}

void	is_in_squote(int *i, char c, int quotes)
{
	if (c == '\'' && !quotes)
		*i += 1;
}

int	quoter(char **tmpcontent, int *quotes, int i, char c)
{
	if ((*tmpcontent)[i] == c)
	{
		ft_rmv_char(tmpcontent, i);
		if (*quotes >= 2)
			*quotes = 0;
		return (1);
	}
	return (0);
}
