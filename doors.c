/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:12:57 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 17:29:06 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_door	*get_door(t_map *map, t_coord coord)
{
	int	i;

	i = 0;
	while (i < map->nr_of_doors)
	{
		if (coord_equals(map->doors[i].coord, coord))
			return (&map->doors[i]);
		map->doors++;
	}
	return (NULL);
}

void	activate_door(t_data *data, t_coord coord, int state)
{
	t_door	*door;

	door = get_door(data->map, coord);
	door->state = state;
	data->active_door = door;
}

void	move_door(t_data *data, t_door *door)
{
	if (door->state == OPENING)
		door->pos += DOOR_STEP;
	else if (door->state == CLOSING)
		door->pos -= DOOR_STEP;
	if (door->pos == 0.0 || door->pos == 1.0)
	{
		door->state = IDLE;
		data->active_door = NULL;
	}
}
