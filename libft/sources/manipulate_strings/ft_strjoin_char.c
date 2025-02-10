/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:15:40 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:15:45 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char    *ft_strjoin_char(char *str, char c)
{
    char    *new;
    int     i;

    i = 0;
    new = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!new)
        return (NULL);
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = c;
    new[i + 1] = '\0';
    free(str);
    return (new);
} 