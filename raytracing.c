#include "cub3d.h"
void cast_rays(char **map, t_player p);
double get_dist(t_ray r, t_coord coll, t_player p);
t_coord get_horiz_coll(t_player p, t_ray r, char **map);
t_coord	get_ray_delta(t_ray r, bool is_horiz);
t_coord get_wall_coll(t_coord coll, t_ray r, char **map, bool is_horiz);
t_coord get_vert_coll(t_player p, t_ray r, char **map);
int check_dir(t_ray r, bool is_horiz);
double deg_to_rad(double degrees);
double radians_to_degrees(double radians) ;

void cast_rays(char **map, t_player p)
{
	int i;
	t_ray r;
	t_coord horiz_coll;
	t_coord vert_coll;

	i = 320;
	r.pos = p.pos;
	while(i < WINDOW_WIDTH)
	{
		r.dir = p.dir - (FOV / 2) + (FOV / WINDOW_WIDTH) * i;
		printf("r.dir: %f\n", radians_to_degrees(r.dir));
		horiz_coll = get_horiz_coll(p, r, map);
		vert_coll = get_vert_coll(p, r, map);
		if(get_dist(r, horiz_coll, p) < get_dist(r, vert_coll, p))
			printf("horiz_coll.x: %f, horiz_coll.y: %f\n", horiz_coll.x, horiz_coll.y);
		else
			printf("vert_coll.x: %f, vert_coll.y: %f\n", vert_coll.x, vert_coll.y);
		printf("HORIZ dist: %f\n", get_dist(r, horiz_coll, p));
		printf("vert dist: %f\n", get_dist(r, vert_coll, p));
		i++;
		printf("i = %d\n", i);
	}
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
	dist = fabs((r.pos.y - coll.y)/ sin(r.dir));
	dist = dist * cos(r.dir - p.dir);
	return (dist);
}

t_coord get_horiz_coll(t_player p, t_ray r, char **map)
{
	t_coord coll;

	if(check_dir(r, true) == NORTH)
		coll.y = floor(p.pos.y/CUBE_SIZE) * CUBE_SIZE - 0.0001;
	else if(check_dir(r, true) == SOUTH)
		coll.y = floor(p.pos.y/CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	coll.x = p.pos.x + (p.pos.y - coll.y) / tan(r.dir);
	coll = get_wall_coll(coll, r, map, true);
	return coll;
}

t_coord	get_ray_delta(t_ray r, bool is_horiz)
{
	t_coord delta;
	if(is_horiz)
	{
		if (check_dir(r, is_horiz) == SOUTH)
			delta.y = CUBE_SIZE;
		else
			delta.y = -CUBE_SIZE;
		delta.x = CUBE_SIZE / tan(r.dir);
	}
	else
	{
		if(check_dir(r, is_horiz) == EAST)
			delta.x = CUBE_SIZE;
		else
			delta.x = -CUBE_SIZE;
		delta.y = CUBE_SIZE * tan(r.dir);
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
	
	while(map[map_x][map_y] != WALL)
	{
		coll.x += delta.x;
		coll.y += delta.y;
		map_x = ((int)floor((coll.x/CUBE_SIZE)));
		map_y = ((int)floor((coll.y/CUBE_SIZE)));
		if (map_x < 0 || map_y < 0 || map_x > 5 || map_y > 4)
			break;
	}
	printf("coll.x: %d, coll.y: %d\n", map_x, map_y);
	return (coll);
}

t_coord get_vert_coll(t_player p, t_ray r, char **map)
{
	t_coord coll;
	if(check_dir(r, false) == EAST)
		coll.x = floor(p.pos.x/CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
	else if(check_dir(r, false) == WEST)
		coll.x = floor(p.pos.x/CUBE_SIZE) * CUBE_SIZE - 0.0001;
	coll.y = p.pos.y + (p.pos.x - coll.x) * tan(r.dir);
	coll = get_wall_coll(coll, r, map, false);
	return (coll);
}


int check_dir(t_ray r, bool is_horiz)
{
	double angle;
	angle = fmod(r.dir, 2 * M_PI);
	if (angle < 0) 
		angle += 2 * M_PI;
	if (is_horiz)
	{
		if (angle > 0 && angle < M_PI)
			return SOUTH;
		else
			return NORTH;
	}
	else
	{
		if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
			return WEST;
		else
			return EAST;
	}
}



