/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:28:42 by phartman          #+#    #+#             */
/*   Updated: 2024/05/03 15:22:45 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_string(const char ch, va_list args)
{
	int	count;

	if (ch == 'c')
	{
		ft_putchar_fd((char)va_arg(args, int), 1);
		count = 1;
	}
	if (ch == 's')
		count = ft_countstr(va_arg(args, char *));
	if (ch == 'p')
		count = ft_print_pointer(va_arg(args, void *));
	if (ch == 'd' || ch == 'i')
		count = ft_countnbr(va_arg(args, int));
	if (ch == 'u')
		count = ft_countnbruns(va_arg(args, unsigned int));
	if (ch == 'x')
		count = ft_print_hex(va_arg(args, int), "0123456789abcdef", 1);
	if (ch == 'X')
		count = ft_print_hex(va_arg(args, int), "0123456789ABCDEF", 1);
	if (ch == '%')
	{
		ft_putchar_fd('%', 1);
		count = 1;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	size_t	i;
	int		count;
	va_list	args;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += parse_string(format[i + 1], args);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

void	ft_putnbruns_fd(unsigned int n, int fd)
{
	if (n >= 10)
	{
		ft_putnbruns_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

