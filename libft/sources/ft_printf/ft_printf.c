/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvalerio <dvalerio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:16:51 by dvalerio          #+#    #+#             */
/*   Updated: 2023/12/08 15:17:37 by dvalerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_printarg(va_list args, char c)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_putchar(va_arg(args, int));
	else if (c == 's')
		size += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		size += ft_printptr(va_arg(args, void *), 'x');
	else if (c == 'd')
		size += ft_printnbr(va_arg(args, int));
	else if (c == 'i')
		size += ft_printnbr(va_arg(args, int));
	else if (c == 'u')
		size += ft_putnbr(va_arg(args, unsigned int));
	else if (c == 'x')
		size += ft_printhex(va_arg(args, unsigned int), 'x');
	else if (c == 'X')
		size += ft_printhex(va_arg(args, unsigned int), 'X');
	else if (c == '%')
		size += ft_putchar('%');
	return (size);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		size;

	i = 0;
	size = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '%')
		{
			size += ft_printarg(args, str[i + 1]);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			size++;
		}
		i++;
	}
	va_end(args);
	return (size);
}
