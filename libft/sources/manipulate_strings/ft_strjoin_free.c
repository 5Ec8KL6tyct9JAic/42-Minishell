/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:15:30 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/02/10 15:15:35 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *str;

    str = ft_strjoin(s1, s2);
    free(s1);
    return (str);
} 