/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:16:51 by dvalerio          #+#    #+#             */
/*   Updated: 2022/10/18 13:08:12 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
//#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	else
	{
		while (dst[i])
			i++;
		ft_strlcpy(&dst[i], src, dstsize - i);
		return (ft_strlen(src) + i);
	}
}
/*
int main()
{
	char src[] = "the cake is a lie !\0I'm hidden lol\r\n";
	char dst[] = "there is no stars in the sky";
	printf("%s\n", src);
	printf("%s\n", dst);
	ft_strlcat(dst, src, ft_strlen
	("the cake is a lie !\0I'm hidden lol\r\n") + 4);
	printf("%zu\n", ft_strlcat
	(dst, src, ft_strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4));
	printf("%s\n", src);
	printf("%s\n", dst);
	return 0;
}*/
