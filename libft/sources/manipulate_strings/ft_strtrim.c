/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:34:12 by dvalerio          #+#    #+#             */
/*   Updated: 2022/10/20 11:16:05 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
//#include <stdio.h>
static int	is_sep(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_start(char *str, char *set)
{
	int	i;

	i = 0;
	while (is_sep(str[i], set) == 1)
		i++;
	return (i);
}

static int	get_end(char *str, char *set)
{
	int	i;

	i = ft_strlen(str);
	while (is_sep(str[i - 1], set) == 1)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (ft_strncmp(s1, set, ft_strlen(s1)) == 0)
		return (ft_strdup(""));
	start = get_start((char *)s1, (char *)set);
	end = get_end((char *)s1, (char *)set);
	if (end == 0 || start == (int)ft_strlen(s1))
		return (ft_strdup(""));
	res = malloc(sizeof(char) * (end - start) + 1);
	if (!res)
		return (NULL);
	while (start < end)
		res[i++] = (char)s1[start++];
	res[i] = '\0';
	return (res);
}
/*
int main()
{
	char str[] = "lorem ipsum dolor sit amet";
	char set[] = "te";
	char *res;
	res = ft_strtrim(str, set);
	printf("%s\n", res);
	return 0;

}*/
