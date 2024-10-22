/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:12:18 by phartman          #+#    #+#             */
/*   Updated: 2024/10/22 14:19:10 by phartman         ###   ########.fr       */
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
