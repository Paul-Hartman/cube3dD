#include "cub3d.h"

int angle_to_index(double angle)
{
    angle = norm_angle(angle);

    int index = (int)(angle * 3600 / (2 * M_PI));
    return index % 3600;
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
