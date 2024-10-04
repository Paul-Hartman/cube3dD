#include "cub3d.h"

double	get_dist(t_ray r, t_coord coll, t_player p);
double	get_horiz_coll(t_player p, t_ray *r, t_map *map);
t_coord	get_ray_delta(t_ray r, bool is_horiz);
t_coord	get_wall_coll(t_coord coll, t_ray r, t_map *map, bool is_horiz);
double	get_vert_coll(t_player p, t_ray *r, t_map *map);
double	deg_to_rad(double degrees);
double	radians_to_degrees(double radians);
int		check_dir(t_ray r, bool is_horiz);

double	projected_wall_height(double dist)
{
	int	focal_len;

	focal_len = (WINDOW_WIDTH / 2.0) / (tan(FOV / 2.0));
	return ((CUBE_SIZE / dist) * focal_len);
}

int	get_tex_offset(t_ray r)
{
	int	tex_x;

	if (r.is_horiz)
		tex_x = (int)r.coll.x % CUBE_SIZE;
	else
		tex_x = (int)r.coll.y % CUBE_SIZE;
	tex_x = (tex_x * TEXTURE_HEIGHT) / CUBE_SIZE;
	return (tex_x);
}


void	draw_walls(t_ray *rays, t_data *data)
{
	int	i;
	int	height;
	int	wall_top;
	double tex_y;
	int	j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		height = (int)projected_wall_height(rays[i].dist);
		wall_top = WINDOW_HEIGHT / 2 - height / 2;
		j = 0;
		while (j < wall_top && j < WINDOW_HEIGHT)
			set_pixel(data, data->ceiling, i, j++);
		while (j < wall_top + height && j < WINDOW_HEIGHT)
		{
			tex_y = ((j - wall_top) * TEXTURE_HEIGHT) / height;
			put_pixel_from_img(data, &data->textures->north,
				(t_coord){get_tex_offset(rays[i]), tex_y}, (t_coord){i, j});
			j++;
		}
		while (j < WINDOW_HEIGHT && j < WINDOW_HEIGHT)
			set_pixel(data, data->floor, i, j++);
		i++;
	}
}

t_ray	*cast_rays(t_map *map, t_player p)
{
	int		i;
	t_ray	r;
	t_ray	*rays;

	i = 0;
	rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	while (i < WINDOW_WIDTH)
	{
		r.dir = p.dir + (FOV / 2) - (FOV / WINDOW_WIDTH) * i;
		r.dir = norm_angle(r.dir);
		r.is_horiz = false;
		if (get_horiz_coll(p, &r, map) < get_vert_coll(p, &r, map))
		{
			r.dist = get_horiz_coll(p, &r, map);
			r.is_horiz = true;
		}
		else
			r.dist = get_vert_coll(p, &r, map);
		rays[i] = r;
		i++;
	}
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		printf("ray[%d] x= %f ray[%d] y= %f is_horiz=%d \n", i, rays[i].coll.x, i, rays[i].coll.y, rays[i].is_horiz);
		printf("ray[%d] y= %f\n", i, rays[i].coll.y);
		i++;
	}
	return (rays);
}

double	norm_angle(double angle)
{
	if(angle >= 2 * M_PI)
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

double	get_dist(t_ray r, t_coord coll, t_player p)
{
	double	dist;
	double	angle_diff;

	if (coll.x == -1.0 && coll.y == -1.0)
		return (INFINITY);
	dist = sqrt(pow(p.pos.x - coll.x, 2) + pow(p.pos.y - coll.y, 2));
	angle_diff = r.dir - norm_angle(p.dir);
	dist = dist * cos(norm_angle(angle_diff));
	return (dist);
}

t_coord	get_ray_delta(t_ray r, bool is_horiz)
{
	t_coord	delta;
	double	tan_val;

	tan_val = fabs(tan(r.dir));
	if (is_horiz)
	{
		if (check_dir(r, is_horiz) == SOUTH)
			delta.y = CUBE_SIZE;
		else
			delta.y = -CUBE_SIZE;
		if (tan_val == 0)
			delta.x = 0;
		else if (check_dir(r, false) == WEST)
			delta.x = -CUBE_SIZE / tan_val;
		else
			delta.x = CUBE_SIZE / tan_val;
	}
	else
	{
		if (check_dir(r, is_horiz) == EAST)
			delta.x = CUBE_SIZE;
		else
			delta.x = -CUBE_SIZE;
		if (tan_val == 0)
			delta.y = 0;
		else if (check_dir(r, true) == NORTH)
			delta.y = -CUBE_SIZE * tan_val;
		else
			delta.y = CUBE_SIZE * tan_val;
	}
	return (delta);
}

bool	is_wall(t_coord pos, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = ((int)floor((pos.x / CUBE_SIZE)));
	map_y = ((int)floor((pos.y / CUBE_SIZE)));
	if (map->grid[map_y][map_x] == WALL)
		return (true);
	return (false);
}

t_coord	get_wall_coll(t_coord coll, t_ray r, t_map *map, bool is_horiz)
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
		if (is_wall(coll, map))
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
	if (check_dir(*r, false) == WEST)
	{
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE - 1;
		tan_val = -tan_val;
	}
	else if (check_dir(*r, false) == EAST)
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (tan_val == 0)
		tan_val = 0.1;
	coll.y = p.pos.y + (p.pos.x - coll.x) * tan_val;
	r->coll = get_wall_coll(coll, *r, map, false);
	dist = get_dist(*r, r->coll, p);
	return (dist);
}

double	get_horiz_coll(t_player p, t_ray *r, t_map *map)
{
	t_coord	coll;
	double	tan_val;

	tan_val = fabs(tan(r->dir));
	if (check_dir(*r, true) == NORTH)
	{
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE - 1;
		tan_val = -tan_val;
	}
	else if (check_dir(*r, true) == SOUTH)
		coll.y = floor(p.pos.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if (tan_val == 0)
		tan_val = 0.1;
	coll.x = p.pos.x + (coll.y - p.pos.y) / tan_val;
	r->coll = get_wall_coll(coll, *r, map, true);
	return (get_dist(*r, r->coll, p));
}

int	check_dir(t_ray r, bool is_horiz)
{
	double	angle;

	angle = r.dir;
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
