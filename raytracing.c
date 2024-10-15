/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:36:33 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/15 20:01:02 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_dist(t_ray *r, t_coord coll, t_player p);
double	get_horiz_coll(t_player p, t_ray *r, t_map *map);
t_coord	get_ray_delta(t_ray *r, bool is_horiz);
t_coord	get_wall_coll(t_coord coll, t_ray *r, t_map *map, bool is_horiz);
double	get_vert_coll(t_player p, t_ray *r, t_map *map);
double	deg_to_rad(double degrees);
double	radians_to_degrees(double radians);
int		check_dir(double angle, bool is_horiz);
t_image	*get_texture(t_textures *textures, t_ray *r);

double	projected_wall_height(int focal_len, double dist)
{
	return ((CUBE_SIZE / dist) * focal_len);
}

int	get_tex_offset(t_ray r)
{
	int	tex_x;

	if (r.is_horiz)
		tex_x = (int)r.coll.x % CUBE_SIZE;
	else
		tex_x = (int)r.coll.y % CUBE_SIZE;

	return (tex_x);
}

void draw_floor(t_data *data, int i, int j, bool is_texture)
{
	t_ray r;
	int tex_x;
	int tex_y;

	if(is_texture)
	{
		r.dist = CHAR_HEIGHT * data->focal_len /  ((double)j - (double)WINDOW_HEIGHT / 2.0) ;
		r.dir = norm_angle(data->player->dir + (FOV / 2.0) - (FOV / WINDOW_WIDTH) * i);
		r.dist = r.dist/ cos(norm_angle(r.dir - data->player->dir));
		r.coll.x = data->player->pos.x + r.dist * cos(r.dir) * 3;
		r.coll.y = data->player->pos.y - r.dist * sin(r.dir) * 3;
		r.coll.x = fmod(r.coll.x, CUBE_SIZE) / CUBE_SIZE;
		r.coll.y = fmod(r.coll.y, CUBE_SIZE)/ CUBE_SIZE;
		tex_x = (int)(r.coll.x  * (TEXTURE_HEIGHT));
		tex_y = (int)(r.coll.y  * (TEXTURE_HEIGHT));
		put_pixel_from_img(data, &data->textures->north, (t_coord){tex_x, tex_y}, (t_coord){i, j});
	}
	else
		set_pixel(data, data->floor, i, j);
}


void draw_ceiling(t_data *data, int i, int j, bool is_texture)
{
	t_ray r;
	int tex_x;
	int tex_y;

	if(is_texture)
	{
		r.dist = CHAR_HEIGHT * data->focal_len /  ((double)j - (double)WINDOW_HEIGHT / 2.0) ;
		r.dir = norm_angle(data->player->dir + (FOV / 2.0) - (FOV / WINDOW_WIDTH) * i);
		r.dist = r.dist/ cos(norm_angle(r.dir - data->player->dir));
		r.coll.x = data->player->pos.x - r.dist * cos(r.dir) * 3;
		r.coll.y = data->player->pos.y + r.dist * sin(r.dir) * 3;
		r.coll.x = fmod(r.coll.x, CUBE_SIZE) / CUBE_SIZE;
		r.coll.y = fmod(r.coll.y, CUBE_SIZE)/ CUBE_SIZE;
		tex_x = (int)(r.coll.x  * (TEXTURE_HEIGHT));
		tex_y = (int)(r.coll.y  * (TEXTURE_HEIGHT));
		put_pixel_from_img(data, &data->textures->north, (t_coord){tex_x, tex_y}, (t_coord){i, j});
	}
	else
		set_pixel(data, data->floor, i, j);
}


void	draw_walls(t_ray *rays, t_data *data)
{
	int		i;
	int		j;
	int		height;
	int		wall_top;
	double	tex_x;
	double	tex_y;
	t_image	*texture;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		height = (int)projected_wall_height(data->focal_len, rays[i].dist);
		texture = get_texture(data->textures, &rays[i]);
		wall_top = WINDOW_HEIGHT / 2 - height / 2;
		j = 0;
		while (j < wall_top && j < WINDOW_HEIGHT)
			draw_ceiling(data, i, j++, true);
		while (j < wall_top + height && j < WINDOW_HEIGHT)
		{
			tex_x = get_tex_offset(rays[i]);
			tex_y = ((j - wall_top) * TEXTURE_HEIGHT) / height;
			put_pixel_from_img(data, texture, (t_coord){tex_x, tex_y},
				(t_coord){i, j});
			j++;
		}
		while (j >= wall_top + height && j < WINDOW_HEIGHT)
		 	draw_floor(data, i, j++, true);
		i++;
	}
	free(rays);
}

t_ray	init_ray(double dir, int i)
{
	t_ray	r;

	r.dir = dir + (FOV / 2) - (FOV / WINDOW_WIDTH) * i;
	r.dir = norm_angle(r.dir);
	r.is_horiz = false;
	return (r);
}

t_ray	update_ray(t_ray *r, double dist, bool is_horiz)
{
	r->dist = dist;
	r->is_horiz = is_horiz;
	return (*r);
}

t_ray	*cast_rays(t_map *map, t_player p)
{
	int		i;
	t_ray	*rays;
	t_ray	ray[2];
	double	horiz_coll;
	double	vert_coll;

	i = 0;
	rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	while (i < WINDOW_WIDTH)
	{
		ray[0] = init_ray(p.dir, i);
		ray[1] = init_ray(p.dir, i);
		horiz_coll = get_horiz_coll(p, &ray[0], map);
		vert_coll = get_vert_coll(p, &ray[1], map);
		if (horiz_coll < vert_coll)
			rays[i] = update_ray(&ray[0], horiz_coll, true);
		else
			rays[i] = update_ray(&ray[1], vert_coll, false);
		i++;
	}
	return (rays);
}

double	norm_angle(double angle)
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / M_PI));
}

double	get_dist(t_ray *r, t_coord coll, t_player p)
{
	double	dist;
	double	angle_diff;

	if (coll.x == -1.0 && coll.y == -1.0)
		return (INFINITY);
	dist = sqrt(pow(p.pos.x - coll.x, 2) + pow(p.pos.y - coll.y, 2));
	angle_diff = r->dir - norm_angle(p.dir);
	dist = dist * cos(norm_angle(angle_diff));
	return (dist);
}

t_coord	get_ray_delta(t_ray *r, bool is_horiz)
{
	t_coord	delta;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (is_horiz)
	{
		if (check_dir(r->dir, true) == SOUTH)
			delta.y = CUBE_SIZE;
		else
			delta.y = -CUBE_SIZE;
		if (tan_val == 0)
			delta.x = 0;
		else if (check_dir(r->dir, false) == WEST)
			delta.x = -CUBE_SIZE / tan_val;
		else
			delta.x = CUBE_SIZE / tan_val;
	}
	else
	{
		if (check_dir(r->dir, false) == EAST)
			delta.x = CUBE_SIZE;
		else
			delta.x = -CUBE_SIZE;
		if (tan_val == 0)
			delta.y = 0;
		else if (check_dir(r->dir, true) == NORTH)
			delta.y = -CUBE_SIZE * tan_val;
		else
			delta.y = CUBE_SIZE * tan_val;
	}
	return (delta);
}

t_image	*get_texture(t_textures *textures, t_ray *r)
{
	int	side;

	if (r->is_door)
		return (&textures->door);
	side = check_dir(r->dir, r->is_horiz);
	if (side == NORTH)
		return (&textures->south);
	if (side == SOUTH)
		return (&textures->north);
	if (side == EAST)
		return (&textures->west);
	if (side == WEST)
		return (&textures->east);
	return (NULL);
}

t_coord	get_wall_coll(t_coord coll, t_ray *r, t_map *map, bool is_horiz)
{
	t_coord	delta;
	int		map_x;
	int		map_y;

	map_x = ((int)floor((coll.x / CUBE_SIZE)));
	map_y = ((int)floor((coll.y / CUBE_SIZE)));
	delta = get_ray_delta(r, is_horiz);
	while (!(map_x < 0 || map_y < 0 || map_x > map->width - 1
			|| map_y > map->height - 1))
	{
		r->map_item = get_map_item(coll, map);
		r->is_door = (r->map_item == DOOR);
		if (r->is_door || r->map_item == WALL)
			return (coll);
		coll.x += delta.x;
		coll.y += delta.y;
		map_x = ((int)floor((coll.x / CUBE_SIZE)));
		map_y = ((int)floor((coll.y / CUBE_SIZE)));
	}
	return ((t_coord){-1.0, -1.0});
}

double	get_vert_coll(t_player p, t_ray *r, t_map *map)
{
	t_coord	coll;
	double	tan_val;
	double	dist;

	tan_val = fabs(tan(r->dir));
	if (check_dir(r->dir, false) == WEST)
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (check_dir(r->dir, true) == NORTH)
		coll.y = p.pos.y - fabs(p.pos.x - coll.x) * tan_val;
	else
		coll.y = p.pos.y + fabs(p.pos.x - coll.x) * tan_val;
	r->coll = get_wall_coll(coll, r, map, false);
	dist = get_dist(r, r->coll, p);
	return (dist);
}

double	get_horiz_coll(t_player p, t_ray *r, t_map *map)
{
	t_coord	coll;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (tan_val == 0)
		return (INFINITY);
	if (check_dir(r->dir, true) == NORTH)
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE - 1;
	else
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (check_dir(r->dir, false) == WEST)
		coll.x = p.pos.x - fabs(p.pos.y - coll.y) / tan_val;
	else
		coll.x = p.pos.x + fabs(p.pos.y - coll.y) / tan_val;
	r->coll = get_wall_coll(coll, r, map, true);
	return (get_dist(r, r->coll, p));
}

int	check_dir(double angle, bool is_horiz)
{
	if (is_horiz)
	{
		if (angle >= 0 && angle < M_PI)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
			return (WEST);
		else
			return (EAST);
	}
}
