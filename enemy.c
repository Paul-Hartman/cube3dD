#include "cub3d.h"

double	get_dir_to(t_coord pos, t_coord target)
{
	return (norm_angle(-atan2(target.y - pos.y, target.x - pos.x)));
}
double	get_scale(double focal_len, double dist)
{
	return (focal_len / dist);
}

void	put_sprite(t_data *data, t_sprite *sprite)
{
	int		i;
	int		j;
	double	scale;
	int		screen_y;
	int		offset;

	i = -1;
	offset = 0;
	scale = get_scale(data->focal_len, get_dist(get_dir_to(data->player->pos,
					sprite->pos), sprite->pos, *data->player));
	screen_y = (WINDOW_HEIGHT / 2 - (int)(sprite->pos.y
				/ get_dist(get_dir_to(data->player->pos, sprite->pos),
					sprite->pos, *data->player)));
	if (sprite->info->middle <= sprite->info->len / 2
		&& sprite->info->len < sprite->width * scale)
		offset = (int)(sprite->width * scale) - sprite->info->len;
	while (++i < (int)(sprite->width * scale) && i < sprite->info->len)
	{
		j = -1;
		while (++j < (int)(sprite->height * scale) && j < WINDOW_HEIGHT
			- screen_y)
		{
			if ((int)(i / scale) >= 0 && i / scale < sprite->width && (int)(j
					/ scale) >= 0 && (int)(j / scale) < sprite->height)
				put_pixel_from_img(data, &data->textures->enemy[data->enemy->frame],
					(t_coord){(int)((i + offset) / scale), (int)(j / scale)},
					(t_coord){sprite->info->min_x + i, screen_y + j});
		}
	}
}

bool	hit_enemy(t_ray *r, t_data *data, double scale)
{
	int		scaled_width;
	double	dir_to_enemy;
	double	left_angle;
	double	right_angle;
	double	screen_width;

	scaled_width = (int)(data->enemy->width * scale);
	screen_width = scaled_width * FOV / WINDOW_WIDTH;
	dir_to_enemy = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y,
				data->enemy->pos.x - data->player->pos.x));
	left_angle = norm_angle(dir_to_enemy - (screen_width / 2.0));
	right_angle = norm_angle(dir_to_enemy + (screen_width / 2.0));
	if ((r->dir >= left_angle && r->dir <= right_angle)
		|| (left_angle > right_angle && (r->dir >= left_angle
				|| r->dir <= right_angle)))
	{
		return (true);
	}
	return (false);
}

t_sprite_info	*set_sprite_info(t_data *data, t_list *info_lst)
{
	int				i;
	double			middle;
	int				closest;
	double			dir_to_enemy;
	t_sprite_info	*info;

	i = 0;
	middle = 100;
	dir_to_enemy = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y,
				data->enemy->pos.x - data->player->pos.x));
	info = (t_sprite_info *)malloc(sizeof(t_sprite_info));
	info->min_x = ((t_sprite_info *)info_lst->content)->screen_x;
	info->len = ft_lstsize(info_lst);
	while (info_lst)
	{
		if (fabs(((t_sprite_info *)info_lst->content)->dir
				- dir_to_enemy) < middle)
		{
			middle = fabs(((t_sprite_info *)info_lst->content)->dir
					- dir_to_enemy);
			closest = i;
		}
		i++;
		info_lst = info_lst->next;
	}
	info->dir = dir_to_enemy;
	info->middle = closest;
	info->max_x = info->min_x + info->len;
	return (info);
}




t_sprite	*get_sprite_coll(t_data *data, t_ray *rays, t_sprite *sprite)
{
	int				i;
	double			dist;
	double			scale;
	t_sprite_info	*sprite_info;
	t_list			*info_lst;

	i = -1;
	dist = sqrt(pow(data->player->pos.x - data->enemy->pos.x, 2)
			+ pow(data->player->pos.y - data->enemy->pos.y, 2));
	scale = data->focal_len / dist;
	info_lst = NULL;
	while (++i < WINDOW_WIDTH)
	{
		if (hit_enemy(&rays[i], data, scale) && rays[i].dist > dist)
		{
			sprite_info = malloc(sizeof(t_sprite_info));
			sprite_info->dir = rays[i].dir;
			sprite_info->screen_x = i;
			ft_lstadd_back(&info_lst, ft_lstnew(sprite_info));
		}
	}
	if (info_lst)
	{
		sprite_info = set_sprite_info(data, info_lst);
		ft_lstclear(&info_lst, free);
		sprite->info = sprite_info;
		return (sprite);
	}
	return (NULL);
}

int move_enemy(t_data *data)
{
	double		dir;
	double		fire_dist;
	t_coord		move;
	double distance;
	dir = get_dir_to(data->enemy->pos, data->player->pos);
	distance = get_dist(dir, data->enemy->pos,
		*data->player);
	fire_dist = 200;
	if (distance <=  fire_dist)
	{
		data->enemy->state = ATTACK;
		return(1);
	}
	data->enemy->state = WALK;
	move.x = MOVE_SPEED * data->cos_table[angle_to_index(dir)];
	move.y = MOVE_SPEED * data->sin_table[angle_to_index(dir)];
	if (!is_wall((t_coord){data->enemy->pos.x + move.x, data->enemy->pos.y + move.y}, data->map))
	{
		data->enemy->pos.x += move.x;
		data->enemy->pos.y -= move.y;
		return (1);
	}
	return (0);
}

// void	move_enemy(t_enemy *enemy, t_vars *vars, int new_x, int new_y)
// {
// 	int	grid_x;
// 	int	grid_y;

// 	grid_x = new_x + enemy->pos.x;
// 	grid_y = new_y + enemy->pos.y;
// 	if (grid_x >= 0 && grid_x < vars->leg.col && grid_y >= 0
// 		&& grid_y < vars->leg.row && vars->map[grid_y][grid_x] != '1')
// 	{
// 		enemy->x = grid_x * CHAR_HEIGHT;
// 		enemy->y = grid_y * CHAR_HEIGHT;
// 		enemy->pos = assign_coord(grid_x, grid_y);
// 	}
// 	else
// 	{
// 		if (!new_x && vars->map[grid_y][grid_x + new_y] == '0')
// 			move_enemy(enemy, vars, new_y, 0);
// 		else if (!new_y && vars->map[grid_y + new_x][grid_x] == '0')
// 			move_enemy(enemy, vars, 0, new_x);
// 		else if (!new_y && vars->map[grid_y + -new_x][grid_x] == '0')
// 			move_enemy(enemy, vars, 0, -new_x);
// 		else if (!new_x && vars->map[grid_y][grid_x + -new_y] == '0')
// 			move_enemy(enemy, vars, -new_y, 0);
// 		else
// 			switch_targets(enemy);
// 	}
// }

// t_coord	pick_enemy_spaces(t_vars *vars, int direction)
// {
// 	t_coord	coord;

// 	if (direction == 1)
// 	{
// 		coord.x = 0;
// 		coord.y = 0;
// 		while (vars->map[coord.y][coord.x] != '0' && coord.x <= vars->leg.col
// 			- 1 && coord.y <= vars->leg.row - 1)
// 		{
// 			coord.x++;
// 			coord.y++;
// 		}
// 	}
// 	else
// 	{
// 		coord.x = vars->leg.col - 1;
// 		coord.y = vars->leg.row - 1;
// 		while (vars->map[coord.y][coord.x] != '0' && coord.x >= 0
// 			&& coord.y >= 0)
// 		{
// 			coord.x--;
// 			coord.y--;
// 		}
// 	}
// 	return (coord);
// }

// int	enemy_init(t_vars *vars)
// {
// 	t_enemy	enemy;

// 	enemy.point_a = pick_enemy_spaces(vars, 0);
// 	enemy.point_b = pick_enemy_spaces(vars, 1);
// 	enemy.pos = enemy.point_a;
// 	enemy.target = enemy.point_b;
// 	enemy.x = enemy.pos.x * CHAR_HEIGHT;
// 	enemy.y = enemy.pos.y * CHAR_HEIGHT;
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.enemy, enemy.x,
// 		enemy.y);
// 	vars->enemy = enemy;
// 	return (0);
// }

// void	switch_targets(t_enemy *enemy)
// {
// 	if (enemy->target.x == enemy->point_a.x
// 		&& enemy->target.y == enemy->point_a.y)
// 		enemy->target = enemy->point_b;
// 	else
// 		enemy->target = enemy->point_a;
// }

// void	update_enemy(t_enemy *enemy, t_vars *vars)
// {
// 	if (enemy->pos.x == enemy->target.x && enemy->pos.y == enemy->target.y)
// 		switch_targets(enemy);
// 	else if (enemy->pos.x != enemy->target.x)
// 	{
// 		if (enemy->pos.x > enemy->target.x)
// 			move_enemy(enemy, vars, -1, 0);
// 		else
// 			move_enemy(enemy, vars, 1, 0);
// 	}
// 	else if (enemy->pos.y != enemy->target.y)
// 	{
// 		if (enemy->pos.y > enemy->target.y)
// 			move_enemy(enemy, vars, 0, -1);
// 		else
// 			move_enemy(enemy, vars, 0, 1);
// 	}
// }

