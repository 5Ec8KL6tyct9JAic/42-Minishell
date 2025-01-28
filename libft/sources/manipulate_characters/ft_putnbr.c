/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:21:14 by dvalerio          #+#    #+#             */
/*   Updated: 2023/12/08 15:16:33 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_len(unsigned int nb)
{
	int				i;
	unsigned int	n;

	i = 0;
	n = nb;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + 48);
	}
	if (n <= 9 && n >= 0)
		ft_putchar(n + 48);
	return (ft_len(n));
}

int	ft_putnbr_unsigned(unsigned int number)
{
	unsigned int	nbr;

	nbr = 0;
	if (number <= 9)
		return (ft_putchar((number + 48)));
	else
	{
		nbr += ft_putnbr_unsigned(number / 10);
		nbr += ft_putchar((number % 10) + 48);
	}
	return (nbr);
}
