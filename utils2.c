/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:01:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 17:29:03 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_item(t_coord pos, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = ((int)floor((pos.x / CUBE_SIZE)));
	map_y = ((int)floor((pos.y / CUBE_SIZE)));
	return (map->grid[map_y][map_x]);
}

bool	coord_equals(t_coord c, t_coord d)
{
	return (c.x == d.x && c.y == d.y);
}
