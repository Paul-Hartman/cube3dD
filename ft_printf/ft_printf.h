/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:46:58 by phartman          #+#    #+#             */
/*   Updated: 2024/05/06 13:46:58 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "libft/libft.h"

void	ft_putnbruns_fd(unsigned int n, int fd);
int		ft_print_hex(long n, char *base, int hex);
int		ft_print_pointer(void *n);
int		ft_countnbr(int n);
int		ft_countnbruns(unsigned int n);
int		ft_countstr(char *str);
int		parse_string(const char ch, va_list args);
int		ft_printf(const char *format, ...);

#endif