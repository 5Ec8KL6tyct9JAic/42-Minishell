#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len_str;

	i = 0;
	j = 0;
	len_str = ft_strlen(s);
	if (start > len_str)
		len = 0;
	else if (len >= len_str)
		len = len_str - start;
	if (ft_calloc((void **)&res, sizeof(char), len + 1))
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			res[j++] = s[i];
		i++;
	}
	return (res);
}

char	*ft_str_include(char *src, char *include, int pos, int skip)
{
	char	*res;
	int		i;
	int		j;

	if (ft_calloc((void **)&res,
			ft_strlen(src) + ft_strlen(include) - skip + 1,
			sizeof(char)))
		return (NULL);
	i = -1;
	while (++i < pos)
		res[i] = src[i];
	j = 0;
	while (include[j])
		res[i++] = include[j++];
	j = pos + skip;
	while (src[j])
		res[i++] = src[j++];
	return (res);
}

int	ft_strchr(char **res, char *str, char c)
{
	while (*str)
	{
		if (*str == c)
		{
			*res = str;
			return (0);
		}
		str++;
	}
	return (1);
}

int	ft_strccmp(char *a, char *b, char c)
{
	size_t	i;

	i = 0;
	while ((a[i] || b[i]) && (a[i] != c || b[i] != c))
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

int	get_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
