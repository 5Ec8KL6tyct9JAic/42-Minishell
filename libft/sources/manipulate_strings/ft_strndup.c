/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:14:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:14:29 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char    *ft_strndup(const char *s, size_t n)
{
    char    *str;
    size_t  len;
    size_t  i;

    len = ft_strlen(s);
    if (n < len)
        len = n;
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (i < len)
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
} 