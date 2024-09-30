#include "cub3d.h"

void cast_rays(char **map, t_player p);
double get_dist(t_ray r, t_coord coll, t_player p);
double get_horiz_coll(t_player p, t_ray r, char **map);
t_coord	get_ray_delta(t_ray r, bool is_horiz);
t_coord get_wall_coll(t_coord coll, t_ray r, char **map, bool is_horiz);
double get_vert_coll(t_player p, t_ray r, char **map);
int check_dir(t_ray r, bool is_horiz);
double deg_to_rad(double degrees);
double radians_to_degrees(double radians) ;
double norm_angle(double angle);

void cast_rays(char **map, t_player p)
{
	int i;
	t_ray r;
	t_coord horiz_coll;
	t_coord vert_coll;

	i = 0;
	r.pos = p.pos;
	while(i < WINDOW_WIDTH)
	{
		r.dir = p.dir - (FOV / 2) + (FOV / WINDOW_WIDTH) * i;
		r.dir = norm_angle(r.dir);
		printf("r.dir: %f\n", radians_to_degrees(r.dir));
		if(get_horiz_coll(p, r, map) < get_vert_coll(p, r, map))
			printf("dist horiz %f", get_horiz_coll(p, r, map));
		else
			printf("dist vert %f", get_vert_coll(p, r, map));
		printf("HORIZ dist: %f\n", get_dist(r, horiz_coll, p));
		printf("vert dist: %f\n", get_dist(r, vert_coll, p));
		i++;
		printf("i = %d\n", i);
	}
}

double norm_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

double deg_to_rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

double radians_to_degrees(double radians) 
{
    return radians * (180.0 / M_PI);
}

double get_dist(t_ray r, t_coord coll, t_player p)
{
	double dist;

	dist = sqrt(pow(p.pos.x - coll.x, 2) + pow(p.pos.y - coll.y, 2));
	(void)r;
	//dist = dist * cos(r.dir - p.dir);
	return (dist);
}



t_coord	get_ray_delta(t_ray r, bool is_horiz)
{
	t_coord delta;
	double tan_val;
	tan_val = tan(r.dir);
	if(is_horiz)
	{
		if (check_dir(r, is_horiz) == SOUTH)
			delta.y = CUBE_SIZE;
		else
			delta.y = -CUBE_SIZE;
		if (tan_val == 0)
			delta.x = 0;
		else
			delta.x = CUBE_SIZE / tan_val;
	}
	else
	{
		if(check_dir(r, is_horiz) == EAST)
			delta.x = CUBE_SIZE;
		else
			delta.x = -CUBE_SIZE;
		if (tan_val == 0)
			delta.y = 0;
		else
			delta.y = CUBE_SIZE * tan_val;
	}
	return delta;
}

t_coord get_wall_coll(t_coord coll, t_ray r, char **map, bool is_horiz)
{
	t_coord delta;
	int map_x;
	int map_y;

	map_x = ((int)floor((coll.x/CUBE_SIZE)));
	map_y = ((int)floor((coll.y/CUBE_SIZE)));

	delta = get_ray_delta(r, is_horiz);
	if(!(map_x < 0 || map_y < 0 || map_x >= 5 || map_y >= 4))
	{
	while(map[map_x][map_y] != WALL && delta.x != 0 && delta.y != 0)
	{
		coll.x += delta.x;
		coll.y += delta.y;
		map_x = ((int)floor((coll.x/CUBE_SIZE)));
		map_y = ((int)floor((coll.y/CUBE_SIZE)));
		if (map_x < 0 || map_y < 0 || map_x >= 5 || map_y >= 4)
			break;
	}
	}
	printf("coll.x: %d, coll.y: %d\n", map_x, map_y);
	return (coll);
}


double get_vert_coll(t_player p, t_ray r, char **map)
{
	t_coord coll;
	double tan_val;

	tan_val = fabs(tan(r.dir));
	if (check_dir(r, false) == WEST)
	{
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE - 1;
		tan_val = -tan_val;
	}
	else if (check_dir(r, false) == EAST)
		coll.x = floor(p.pos.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;

	if (tan_val == 0)
		tan_val = 0.1;

	coll.y = p.pos.y + (coll.x - p.pos.x) * tan_val;
	coll = get_wall_coll(coll, r, map, false);
	return get_dist(r, coll, p);
}


double get_horiz_coll(t_player p, t_ray r, char **map)
{
	t_coord coll;
	double tan_val;

	tan_val = fabs(tan(r.dir));
	if(check_dir(r, true) == NORTH)
	{
		coll.y = floor(p.pos.y/CUBE_SIZE) * CUBE_SIZE - 1;
		tan_val = -tan_val;
	}
	else if(check_dir(r, true) == SOUTH)
		coll.y = floor(p.pos.y/CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	if(tan_val == 0)
		tan_val = 0.1;
	coll.x = p.pos.x + (coll.y -p.pos.y) / tan_val;
	coll = get_wall_coll(coll, r, map, true);
	return (get_dist(r, coll, p));
}


int check_dir(t_ray r, bool is_horiz)
{
	double angle;
	angle = r.dir;
	if (is_horiz)
	{
		if (angle >= 0 && angle < M_PI)
			return SOUTH;
		else
			return NORTH;
	}
	else
	{
		if (angle >= M_PI / 2 && angle < 3 * M_PI / 2)
			return WEST;
		else
			return EAST;
	}
}



