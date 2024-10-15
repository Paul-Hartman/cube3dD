/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:14:38 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/15 20:14:39 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall(t_coord pos, t_map *map)
{
	char	map_item;

	map_item = get_map_item(pos, map);
	if (map_item == DOOR || map_item == WALL)
		return (true);
	return (false);
}

int	angle_to_index(double angle)
{
	int	n_angle;
	int	index;

	n_angle = norm_angle(angle);
	index = (int)(n_angle * 3600 / (2 * M_PI));
	return (index % 3600);
}


bool	move_player(t_data *data, bool rev)
{
	t_coord	move;
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (rev)
		move_speed *= -1;
	move.x = move_speed * data->cos_table[angle_to_index(data->player->dir)];
	move.y = move_speed * data->sin_table[angle_to_index(data->player->dir)];

	if (!is_wall((t_coord){data->player->pos.x + move.x, data->player->pos.y
			- move.y}, data->map))
	{
		data->player->pos.x += move.x;
		data->player->pos.y -= move.y;
	}
	return (true);
}




bool	strafe_player(t_data *data, bool left)
{
	t_coord	move;
	double	strafe_dir;

	if (left)
		strafe_dir = data->player->dir + M_PI / 2;
	else
		strafe_dir = data->player->dir - M_PI / 2;
	move.x = MOVE_SPEED * data->cos_table[angle_to_index(strafe_dir)];
	move.y = MOVE_SPEED * data->sin_table[angle_to_index(strafe_dir)];
	if (!is_wall((t_coord){data->player->pos.x + move.x, data->player->pos.y
			- move.y}, data->map))
	{
		data->player->pos.x += move.x;
		data->player->pos.y -= move.y;
	}
	return (true);
}

bool	rotate_player(t_data *data, bool left, double rotate_speed)
{
	if (left)
		rotate_speed *= -1;
	data->player->dir -= rotate_speed;
	data->player->dir = norm_angle(data->player->dir);
	return (true);
}
