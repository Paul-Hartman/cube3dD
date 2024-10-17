#include "cub3d.h"

// void put_sprite(t_data *data, t_list *sprite_hits)
// {
// 	int i;
// 	int j;
// 	double dist;
// 	double scale;
// 	int screen_x;
// 	int screen_y;
// 	int draw_x;
// 	int draw_y;
	
// 	dist = sqrt(pow(data->player->pos.x - data->enemy->pos.x, 2) + pow(data->player->pos.y - data->enemy->pos.y, 2));
// 	scale =data->focal_len / dist;
// 	screen_x = (data->enemy->pos.x - data->player->pos.x) * scale + WINDOW_WIDTH / 2;
// 	screen_y = (data->enemy->pos.y - data->player->pos.y) * scale + WINDOW_HEIGHT / 2;
	
// 	i = 0;
// 	while(i < (int)(data->enemy->width) * scale)
// 	{
// 		j = 0;
// 		while(j < (int)(data->enemy->height) * scale)
// 		{
// 			if((int)(i/ scale) >= 0 && (int)(i/ scale) < data->enemy->width && (int)(j/scale) >= 0 && (int)(j/scale) < data->enemy->height)
// 			{
// 				draw_x = screen_x + i - (data->enemy->width * scale) / 2;
// 				draw_y = screen_y + j - (data->enemy->height * scale) / 2;
// 				put_pixel_from_img(data, &data->textures->enemy, (t_coord){(int)(i/ scale), (int)(j/scale)}, (t_coord){draw_x, draw_y});
// 			}
				
// 			j++;
// 		}
// 		i++;
// 	}
// }


// wall_top = WINDOW_HEIGHT / 2 - height / 2;
// 		j = 0;
// 		while (j < wall_top && j < WINDOW_HEIGHT)
// 			draw_ceiling(data, i, j++, data->textures->south.img_ptr != NULL);
// 		while (j < wall_top + height && j < WINDOW_HEIGHT)
// 		{
// 			tex_x = get_tex_offset(rays[i]);
// 			tex_y = ((j - wall_top) * TEXTURE_HEIGHT) / height;
// 			put_pixel_from_img(data, &data->textures->north, (t_coord){tex_x, tex_y}, (t_coord){i, j});
// 			j++;

// void	draw_walls(t_ray *rays, t_data *data)
// {
// 	int		i;
// 	int		height;
// 	int		wall_top;
// 	double	tex_x;
// 	double	tex_y;
// 	int		j;

// 	i = 0;
// 	while (i < WINDOW_WIDTH)
// 	{
// 		height = (int)projected_wall_height(data->focal_len, rays[i].dist);
// 		wall_top = WINDOW_HEIGHT / 2 - height / 2;
// 		j = 0;
// 		while (j < wall_top && j < WINDOW_HEIGHT)
// 			draw_ceiling(data, i, j++, data->textures->south.img_ptr != NULL);
// 		while (j < wall_top + height && j < WINDOW_HEIGHT)
// 		{
// 			tex_x = get_tex_offset(rays[i]);
// 			tex_y = ((j - wall_top) * TEXTURE_HEIGHT) / height;
// 			put_pixel_from_img(data, &data->textures->north, (t_coord){tex_x, tex_y}, (t_coord){i, j});
// 			j++;
// 		}
// 		while (j >= wall_top + height && j < WINDOW_HEIGHT)
// 		 	draw_floor(data, i, j++, data->textures->south.img_ptr != NULL);
// 		i++;
// 	}
// 	free(rays);
// }




void put_sprite(t_data *data, t_list *sprite_hits)
{
	int i;
	int j;
	double dist;
	double scale;
	int screen_x;
	int screen_y;
	//int draw_x;
	int draw_y;
	i = 0;
	dist = sqrt(pow(data->player->pos.x - data->enemy->pos.x, 2) + pow(data->player->pos.y - data->enemy->pos.y, 2));
	scale = data->focal_len / dist;
	int height =(int)data->enemy->height * scale;
	int width = (int)data->enemy->width * scale;
	screen_y = WINDOW_HEIGHT / 2 - height/2;
	//printf("they equal %d\n", ft_list_size(sprite_hits));
	int size  = ft_lstsize(sprite_hits);
	printf("size: %d  width %d\n", size, width);
	while(i < width && sprite_hits)
	{
		
		
		
		screen_x = ((t_sprite_hit *)sprite_hits->content)->screen_x;
		
		//ft_printf("list size: %d\n", screen_x);
			j = 0;
			while(j < height) 
			{
				  //   int tex_x = (i * data->enemy->width) / width;
       			// int tex_y = (j * data->enemy->height) / height;
				draw_y = screen_y + j;
				
		
				
				put_pixel_from_img(data, &data->textures->enemy, (t_coord){(int)i/scale, (int)j/scale}, (t_coord){screen_x, draw_y});
				j++;
			}
			i++;
			sprite_hits = sprite_hits->next;
		
	}
	ft_lstclear(&sprite_hits, free);
}

// bool is_facing_enemy(t_data *data)
// {
// 	double angle_to_enemy = atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x);
	
// 	angle_to_enemy = norm_angle(angle_to_enemy);
// 	double fov_left = norm_angle(data->player->dir - (FOV / 2.0));
//     double fov_right = norm_angle(data->player->dir + (FOV / 2.0));
// 	if (fov_left < fov_right)
//         return (angle_to_enemy >= fov_left && angle_to_enemy <= fov_right);
//     else
//         return (angle_to_enemy >= fov_left || angle_to_enemy <= fov_right);
// }

bool hit_scaled(t_ray r, t_data *data, double scale)
{

	int scaled_width = (int)(data->enemy->width * scale);
	double enemy_center_angle;
	double left_angle;
	double right_angle;
	double enemy_angular_width = scaled_width * FOV / WINDOW_WIDTH;
	
	


	if (check_dir(r, r.is_horiz) == SOUTH)
	{
		enemy_center_angle = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x));
	left_angle = norm_angle(enemy_center_angle - (enemy_angular_width / 2.0));
 	right_angle = norm_angle(enemy_center_angle + (enemy_angular_width / 2.0));

		
		
	}
	else if (check_dir(r, r.is_horiz) == NORTH)
	{
		
			enemy_center_angle = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x));
		left_angle = norm_angle(enemy_center_angle - (enemy_angular_width / 2.0));
 		right_angle = norm_angle(enemy_center_angle + (enemy_angular_width / 2.0));

	}
	else if (check_dir(r, r.is_horiz) == EAST)
	{
		enemy_center_angle = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x));
		left_angle = norm_angle(enemy_center_angle - (enemy_angular_width / 2.0));
 		right_angle = norm_angle(enemy_center_angle + (enemy_angular_width / 2.0));

			
	}
	else if (check_dir(r, r.is_horiz) == WEST)
	{ 
		enemy_center_angle = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x));
		left_angle = norm_angle(enemy_center_angle - (enemy_angular_width / 2.0));
 		right_angle = norm_angle(enemy_center_angle + (enemy_angular_width / 2.0));

			
	}
	
	if ((r.dir >= left_angle && r.dir <= right_angle) || (left_angle > right_angle && (r.dir >= left_angle || r.dir <= right_angle)))
	{
		
		printf("%f  <  %f    <  %f\n", left_angle, r.dir, right_angle);


		
		
		return (true);
	}
	
	return (false);


	if(r.dir >= left_angle && r.dir <= right_angle)
	{
		
		printf("%f  <  %f    <  %f\n", left_angle, r.dir, right_angle);
		return (1);
	}
		
	
	return (0);
}

// bool hits_enemy(t_ray r, t_data *data, double scale)
// {
// 	int half_width_scaled = (int)(data->enemy->width * scale)/ 2.0;
// 	double left_x, right_x, left_y, right_y;
// 	double left_angle;
// 	double right_angle;
	


// 	//double angle_per_pixel = fov_radians / WINDOW_WIDTH;
	
	
// 	if (check_dir(r, r.is_horiz) == SOUTH)
// 	{
		
// 		left_x = data->enemy->pos.x - half_width_scaled;
// 		right_x = data->enemy->pos.x + half_width_scaled;
		
// 		left_angle = -atan2(data->enemy->pos.y - data->player->pos.y, left_x - data->player->pos.x);
// 		right_angle = -atan2(data->enemy->pos.y - data->player->pos.y, right_x - data->player->pos.x);
		
// 	}
// 	else if (check_dir(r, r.is_horiz) == NORTH)
// 	{
// 		left_x = data->enemy->pos.x + half_width_scaled;
// 		right_x = data->enemy->pos.x - half_width_scaled;

// 		left_angle =  -atan2(data->enemy->pos.y - data->player->pos.y, left_x - data->player->pos.x);
// 		right_angle = -atan2(data->enemy->pos.y - data->player->pos.y, right_x - data->player->pos.x);
			
// 	}
// 	else if (check_dir(r, r.is_horiz) == EAST)
// 	{
// 		left_y = data->enemy->pos.y - half_width_scaled;
// 		right_y = data->enemy->pos.y + half_width_scaled;
// 		left_angle = atan2(left_y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x);
// 		right_angle = atan2(right_y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x);
			
// 	}
// 	else if (check_dir(r, r.is_horiz) == WEST)
// 	{ 
// 		left_y = data->enemy->pos.y + half_width_scaled;
// 		right_y = data->enemy->pos.y - half_width_scaled;
// 		left_angle = atan2(left_y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x);
// 		right_angle = atan2(right_y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x);
			
// 	}
// 	left_angle = norm_angle(left_angle);
// 	right_angle = norm_angle(right_angle);
// 	if (r.dir >= left_angle && r.dir <= right_angle)
// 	{
		
// 		//printf("%f  <  %f    <  %f", left_angle, r.dir, right_angle);


		
		
// 		return (true);
// 	}
	
// 	return (false);
	
// }


// bool ray_hit_enemy(t_ray *r, t_data *data, double scale, double dist)
// {
// 	double max_bound;
// 	double min_bound;
// 	//double angle_to_enemy;
// 	//angle_to_enemy = norm_angle(-atan2(data->enemy->pos.y - data->player->pos.y, data->enemy->pos.x - data->player->pos.x));
// 	// double min_ang =  norm_angle(data->player->dir - FOV / 2.0);
// 	// double max_ang =  norm_angle(data->player->dir + FOV / 2.0);
	
	
	

// 	if(r->dist < dist)
// 		return (false);
// 	if (r->is_horiz)
// 	{
// 		min_bound = fmin(data->enemy->pos.x + (data->enemy->width * scale) / 2, data->enemy->pos.x- (data->enemy->width * scale) / 2);
// 		max_bound = fmax(data->enemy->pos.x + (data->enemy->width * scale) / 2, data->enemy->pos.x - (data->enemy->width * scale) / 2);

// 		if (r->coll.x >= min_bound && r->coll.x <= max_bound)
//             return true;
// 	}
// 	else
// 	{
// 		min_bound = fmin(data->enemy->pos.y + (data->enemy->width * scale) / 2, data->enemy->pos.y - (data->enemy->width * scale) / 2);
// 		max_bound = fmax(data->enemy->pos.y + (data->enemy->width * scale) / 2, data->enemy->pos.y - (data->enemy->width * scale) / 2);

// 		if (r->coll.y >= min_bound && r->coll.y <= max_bound)
//             return true;
// 	}
// 	return(false);
// }


 t_list *get_sprite_coll(t_data *data, t_ray *rays)
 {
	int i;
	i= 0;
	bool is_visible;
	is_visible = false;
	double dist;
	double scale;
	t_sprite_hit *sprite_hit;
	t_list *sprite_colls;
	sprite_colls = NULL;
	
	// double angle_diff;
	// angle_diff = fabs(norm_angle(angle_to_enemy- data->player->dir));
	dist = sqrt(pow(data->player->pos.x - data->enemy->pos.x, 2) + pow(data->player->pos.y - data->enemy->pos.y, 2));
	scale = data->focal_len / dist;

	while(i < WINDOW_WIDTH)
	{	
		
		if(hit_scaled(rays[i], data, scale))
		{
			sprite_hit = malloc(sizeof(t_sprite_hit));
			sprite_hit->is_collect = false;
			if(sprite_hit == NULL)
			{
				ft_lstclear(&sprite_colls, free);
				return (NULL);
			}
			sprite_hit->pos = rays[i].coll;
			sprite_hit->is_enemy = true;
			sprite_hit->screen_x = i;
			sprite_hit->is_horiz = rays[i].is_horiz;
			printf("screen_x: %d\n", sprite_hit->screen_x);
			ft_lstadd_back(&sprite_colls, ft_lstnew(sprite_hit));
			is_visible = true;
		}
		i++;
	}
	if(is_visible)
		return (sprite_colls);
		
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