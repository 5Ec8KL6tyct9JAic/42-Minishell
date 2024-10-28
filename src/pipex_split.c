/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:38:53 by dvalerio          #+#    #+#             */
/*   Updated: 2023/12/26 17:54:55 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_strs(char const *s, char c)
{
	int		nb;

	nb = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		nb++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (nb);
}

static int	ft_strlen_c(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*result;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < n)
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

static void	ft_free_arr(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != NULL)
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;
	size_t	i;

	count = ft_count_strs(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		result[i] = ft_strndup(s, ft_strlen_c(s, c));
		if (result[i] == NULL)
		{
			ft_free_arr(result);
			return (0);
		}
		s += ft_strlen_c(s, c);
		i++;
	}
	result[count] = 0;
	return (result);
}
