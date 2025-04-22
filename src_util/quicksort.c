#include "minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(char **str, int lo, int hi)
{
	int	pi;
	int	i;
	int	j;

	pi = hi;
	i = lo - 1;
	j = lo;
	while (j < hi)
	{
		if (ft_strccmp(str[j], str[pi], '=') < 0)
			ft_swap(str + j, str + ++i);
		j++;
	}
	ft_swap(str + ++i, str + hi);
	return (i);
}

int	quicksort(char **str, int lo, int hi)
{
	int	pi;

	if (lo < hi)
	{
		pi = partition(str, lo, hi);
		quicksort(str, lo, pi - 1);
		quicksort(str, pi + 1, hi);
	}
	return (0);
}
