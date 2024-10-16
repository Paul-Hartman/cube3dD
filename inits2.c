/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:44:03 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 17:07:02 by wpepping         ###   ########.fr       */
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

int	init_doors(t_map *map)
{
	int	i;
	int	j;

	map->nr_of_doors = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i++] == DOOR)
				map->nr_of_doors++;
	}
	if (map->nr_of_doors != 0)
	{
		map->doors = ft_calloc(map->nr_of_doors, sizeof(t_door));
		if (map->doors == NULL)
			return (-1);
	}
	return (0);
}
