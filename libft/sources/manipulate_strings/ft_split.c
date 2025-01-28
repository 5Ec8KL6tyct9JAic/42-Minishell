/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:02:07 by dvalerio          #+#    #+#             */
/*   Updated: 2023/12/08 15:18:55 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (finish - start) + 1);
	if (!res)
		return (NULL);
	while (start < finish)
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}

char	**ft_split(char const *str, char const c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = 0;
	j = 0;
	res = malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!str || !res)
		return (0);
	index = -1;
	while (i <= ft_strlen(str))
	{
		if (str[i] != c && index < 0)
			index = i;
		else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
		{
			res[j++] = word_dup(str, index, i);
			index = -1;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}
