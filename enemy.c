#include "cub3d.h"

double get_dir_to(t_coord pos, t_coord target)
{
	return (norm_angle(-atan2(target.y - pos.y, target.x - pos.x)));
}


void	put_sprite(t_data *data, t_list *sprite_hits, t_sprite sprite)
{
	int		i;
	int		j;
	double	dist;
	double	scale;
	int		screen_x;
	int		screen_y;
	int		draw_y;
	int		height;
	int		width;
	int		size;
	int		tex_x;
	int		tex_y;

	i = 0;
	//double angle = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y,
			//	data->enemy->pos.x - data->player->pos.x));
	double angle = norm_angle(-atan2(sprite.pos.y - data->player->pos.y,
				sprite.pos.x - data->player->pos.x));
	dist = get_dist(angle, sprite.pos, *data->player);
	scale = data->focal_len / dist;
	height = (int)sprite.height * scale;
	width = (int)sprite.width * scale;
	screen_y = (WINDOW_HEIGHT / 2 - (int)(sprite.pos.y / dist)) + height
		/ 2;
	size = ft_lstsize(sprite_hits);

	if (((t_sprite_hit *)sprite_hits->content)->middle <= size / 2
		&& size < width)
		i = width - size;
	while (i < width && sprite_hits)
	{
		screen_x = ((t_sprite_hit *)sprite_hits->content)->screen_x;
		j = 0;
		while (j < height && j < WINDOW_HEIGHT - screen_y)
		{
			draw_y = screen_y + j;
			tex_x = (int)(i / scale) % sprite.width;
			tex_y = (int)(j / scale) % sprite.height;
			if (tex_x >= 0 && tex_x < sprite.width && tex_y >= 0
				&& tex_y < sprite.height)
				put_pixel_from_img(data, &data->textures->enemy,
					(t_coord){tex_x, tex_y}, (t_coord){screen_x, draw_y});
			j++;
		}
		i++;
		sprite_hits = sprite_hits->next;
	}
	ft_lstclear(&sprite_hits, free);
	sprite_hits = NULL;
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
		return (true);
	return (false);
}

int	set_middle(t_data *data, t_list *sprite_colls)
{
	int		i;
	double	middle;
	int		closest;
	double	dir_to_enemy;

	i = 0;
	middle = 100;
	dir_to_enemy = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y,
				data->enemy->pos.x - data->player->pos.x));
	while (sprite_colls)
	{
		if (fabs(((t_sprite_hit *)sprite_colls->content)->dir
				- dir_to_enemy) < middle)
		{
			middle = fabs(((t_sprite_hit *)sprite_colls->content)->dir
					- dir_to_enemy);
			closest = i;
		}
		i++;
		sprite_colls = sprite_colls->next;
	}
	return (closest);
}

t_list	*get_sprite_coll(t_data *data, t_ray *rays)
{
	int				i;
	bool			is_visible;
	double			dist;
	double			scale;
	t_sprite_hit	*sprite_hit;
	t_list			*sprite_colls;

	i = 0;
	sprite_colls = NULL;
	is_visible = false;
	dist = sqrt(pow(data->player->pos.x - data->enemy->pos.x, 2)
			+ pow(data->player->pos.y - data->enemy->pos.y, 2));
	scale = data->focal_len / dist;
	while (i < WINDOW_WIDTH)
	{
		if (hit_enemy(&rays[i], data, scale) && rays[i].dist > dist)
		{
			sprite_hit = malloc(sizeof(t_sprite_hit));
			sprite_hit->is_collect = false;
			if (sprite_hit == NULL)
			{
				ft_lstclear(&sprite_colls, free);
				return (NULL);
			}
			// sprite_hit->dist = rays[i].dist;
			sprite_hit->middle = -1;
			sprite_hit->dir = rays[i].dir;
			sprite_hit->is_enemy = true;
			sprite_hit->screen_x = i;
			ft_lstadd_back(&sprite_colls, ft_lstnew(sprite_hit));
			is_visible = true;
		}
		i++;
	}
	if (is_visible)
	{
		((t_sprite_hit *)sprite_colls->content)->middle = set_middle(data,
				sprite_colls);
		return (sprite_colls);
	}
	return (NULL);
}

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