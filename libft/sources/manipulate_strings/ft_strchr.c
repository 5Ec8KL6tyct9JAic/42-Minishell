/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:41:14 by dvalerio          #+#    #+#             */
/*   Updated: 2022/10/20 11:15:07 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			res = (char *)&s[i];
			return (res);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		res = (char *)(s + i);
		return (res);
	}
	return (NULL);
}
