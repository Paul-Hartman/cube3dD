#include "cub3d.h"

bool	move_player(t_data *data, bool rev)
{
	t_coord	move;
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (rev)
		move_speed *= -1;
	move.x = move_speed * cos(data->player->dir);
	move.y = move_speed * sin(data->player->dir);
	if (!is_wall((t_coord){data->player->pos.x - move.x, data->player->pos.y
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
	move.x = MOVE_SPEED * cos(strafe_dir);
	move.y = MOVE_SPEED * sin(strafe_dir);
	if (!is_wall((t_coord){data->player->pos.x - move.x, data->player->pos.y
			- move.y}, data->map))
	{
		data->player->pos.x += move.x;
		data->player->pos.y -= move.y;
	}
	return (true);
}

bool	rotate_player(t_data *data, bool left)
{
	double	rotate_speed;

	rotate_speed = ROTATE_SPEED;
	if (left)
		rotate_speed *= -1;
	data->player->dir -= rotate_speed;
	data->player->dir = norm_angle(data->player->dir);
	return (true);
}
