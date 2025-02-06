/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:19:07 by dvalerio          #+#    #+#             */
/*   Updated: 2022/10/20 11:15:44 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(tofind) == 0 || str == tofind)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < len && str[i + j])
			j++;
		if (j == ft_strlen(tofind))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char str[] = "A";
//	char tofind[] = "MZIRIBMZE";
	char *res;
	res = ft_strnstr(str, str, ft_strlen(str) + 1);
	printf("%s\n", res);
	return 0;
}*/
