/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:55:51 by phartman          #+#    #+#             */
/*   Updated: 2024/05/03 15:33:03 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(long n, char *base, int hex)
{
	unsigned long	num;
	int				count;
	char			output[16];
	int				i;

	i = 0;
	count = 0;
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	if (hex)
		num = n & 0xFFFFFFFF;
	else
		num = n;
	while (num > 0 && count++ <= 16)
	{
		output[i++] = base[num & 0xF];
		num >>= 4;
	}
	while (i > 0)
		ft_putchar_fd(output[--i], 1);
	return (count);
}

int	ft_print_pointer(void *n)
{
	unsigned long	address;
	int				count;

	if (!n)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	count = 2;
	address = (unsigned long)n;
	ft_putstr_fd("0x", 1);
	count += ft_print_hex(address, "0123456789abcdef", 0);
	return (count);
}

int	ft_countnbr(int n)
{
	int				count;
	unsigned int	num;

	count = 1;
	ft_putnbr_fd(n, 1);
	if (n < 0)
	{
		num = -n;
		count++;
	}
	else
		num = n;
	while (num >= 10)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	ft_countnbruns(unsigned int n)
{
	int	count;

	count = 1;
	ft_putnbruns_fd(n, 1);
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_countstr(char *str)
{
	int	count;

	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (count);
}
