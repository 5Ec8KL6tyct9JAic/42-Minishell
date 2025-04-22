#include "minishell.h"

size_t	ft_strlcat(char *dst, char *src, size_t max_len)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	res;
	size_t	i;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst < max_len)
		res = len_dst + len_src;
	else
		res = max_len + len_src;
	if (len_src == 0)
		return (res);
	while (src[i] && len_dst < max_len - 1)
		dst[len_dst++] = src[i++];
	dst[len_dst] = 0;
	return (res);
}

int	ft_strjoin(char **buff, char *a, char *b)
{
	size_t	len_max;

	len_max = ft_strlen(a) + ft_strlen(b) + 1;
	if (ft_calloc((void **)buff, len_max, sizeof(char)))
		return (1);
	if (ft_strlcat(*buff, a, len_max) > len_max
		|| ft_strlcat(*buff, b, len_max + 1) > len_max)
		return (1);
	return (0);
}

int	free_split(char **element)
{
	int	i;

	i = 0;
	while (element[i])
		del_malloc(element[i++]);
	del_malloc(element);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	min;
	size_t	max;

	min = 0;
	while (is_in_charset(s1[min], set) && s1[min] != '\0')
		min++;
	max = ft_strlen(s1);
	while (is_in_charset(s1[max - 1], set) && max - 1 > 0)
		max--;
	res = ft_substr(s1, min, max - min);
	return (res);
}
