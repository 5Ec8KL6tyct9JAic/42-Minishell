/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:07:27 by dvalerio          #+#    #+#             */
/*   Updated: 2023/04/21 08:59:00 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_ptrlen(unsigned long long n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_ptrval(unsigned long long n, const char form)
{
	if (n >= 16)
	{
		ft_ptrval(n / 16, form);
		ft_ptrval(n % 16, form);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + 48);
		else
		{
			if (form == 'x')
				ft_putchar(n - 10 + 'a');
			if (form == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_printptr(void *n, const char form)
{
	if (n == 0)
	{
		ft_putstr("0x0");
		return (3);
	}
	else
	{
		ft_putstr("0x");
		ft_ptrval((unsigned long long)n, form);
	}
	return (ft_ptrlen((unsigned long long) n) + 2);
}
