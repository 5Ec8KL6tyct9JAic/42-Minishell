#include "utils.h"

static size_t	max_len(int nb)
{
	size_t	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	ft_fill_itoa(int nb, char *buff, size_t len)
{
	size_t	i;

	i = len;
	if (nb < 0)
	{
		buff[0] = '-';
		nb *= -1;
		buff++;
		i--;
	}
	while (i-- > 0)
	{
		buff[i] = '0' + (nb % 10);
		nb /= 10;
	}
}

int	ft_itoa(char **res, int n)
{
	size_t	len;

	if (n >= 2147483647)
		return (ft_strdup(res, "2147483647"));
	if (n <= -2147483648)
		return (ft_strdup(res, "-2147483648"));
	len = max_len(n);
	if (ft_calloc((void **)res, sizeof(char), len + 1))
		return (1);
	ft_fill_itoa(n, *res, len);
	return (0);
}
