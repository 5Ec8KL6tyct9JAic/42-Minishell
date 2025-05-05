/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouaffa <mmouaffa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:51:04 by mmouaffa          #+#    #+#             */
/*   Updated: 2025/05/05 13:51:05 by mmouaffa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

int	ft_malloc(void **element, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (1);
	*element = new;
	add_front(new);
	return (0);
}

int	ft_calloc(void **element, size_t len, size_t nbr)
{
	if (ft_malloc(element, len * nbr))
		return (1);
	ft_memset(*element, 0, len * nbr);
	return (0);
}

int	ft_realloc(void **element, size_t old_size, size_t new_size)
{
	void	*old;

	old = *element;
	if (!*element)
		return (ft_calloc(element, new_size, 1));
	if (ft_calloc(element, new_size, 1)
		|| ft_memcpy(*element, old, old_size)
		|| del_malloc(old))
		return (1);
	return (0);
}
