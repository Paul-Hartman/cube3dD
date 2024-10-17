/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:44:03 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/17 15:03:54 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_trig_tables(double *sin_table, double *cos_table)
{
	double	angle;
	int		i;

	i = 0;
	while (i < 3600)
	{
		angle = deg_to_rad(i * 0.1);
		sin_table[i] = sin(angle);
		cos_table[i] = cos(angle);
		i++;
	}
}

static int	nr_of_doors(t_map *map)
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
			if (map->grid[j++][i] == DOOR)
				result++;
		i++;
	}
	return (result);
}

int	init_doors(t_map *map)
{
	int	i;
	int	j;
	int	n;

	map->nr_of_doors = nr_of_doors(map);
	if (map->nr_of_doors != 0)
	{
		map->doors = malloc(map->nr_of_doors * sizeof(t_door));
		if (map->doors == NULL)
			return (-1);
	}
	n = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == DOOR)
				map->doors[n] = (t_door){(t_coord){i, j - 1}, IDLE, 0, 0};
		i++;
	}
	return (0);
}
