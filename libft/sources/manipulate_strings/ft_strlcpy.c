/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:26:29 by dvalerio          #+#    #+#             */
/*   Updated: 2022/10/18 13:01:15 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
//#include <stdio.h>
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!dst && !src)
		return (0);
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

/*
int main()
{
	char str[] = "the cake is a lie !\0I'm hidden lol\r\n";
	char dst[0xF00];

	printf("%s\n", str);
	printf("%s\n", dst);
	ft_strlcpy(dst, str, ft_strlen(dst));
	printf("%s\n", str);
	printf("%s\n", dst);
	return 0;
}*/
