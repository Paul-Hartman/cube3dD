/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:54:58 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/30 19:55:00 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_isnum(char *str)
{
	while (str)
		if (!ft_isdigit(*(str++)))
			return (false);
	return (true);
}

double	get_angle(char dir)
{
	if (dir == NORTH)
		return (1.5 * M_PI);
	if (dir == EAST)
		return (0);
	if (dir == SOUTH)
		return (0.5 * M_PI);
	else
		return (M_PI);
}

char	*ft_remove(char *str, char c)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	while (str[i])
		if (str[i++] != c)
			len++;
	result = malloc((len + 1) * sizeof(char));
	while (i >= 0)
	{
		if (str[i] != c)
			result[len--] = str[i];
		i--;
	}
	return (result);
}
