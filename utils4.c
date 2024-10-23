/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:18 by phartman          #+#    #+#             */
/*   Updated: 2024/10/23 18:15:03 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	nr_of_thing(t_map *map, int thing)
{
	int	i;
	int	j;
	int	result;

	result = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == thing)
				result++;
		i++;
	}
	return (result);
}

int	angle_to_index(double angle)
{
	double	n_angle;
	int		index;

	n_angle = norm_angle(angle);
	index = (int)(n_angle * 3600 / (2 * M_PI));
	return (index % 3600);
}
