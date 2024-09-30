#include "cub3d.h"

double get_dist(t_ray r, t_coord coll, t_player p);
double get_horiz_coll(t_player p, t_ray r, char **map);
t_coord	get_ray_delta(t_ray r, bool is_horiz);
t_coord get_wall_coll(t_coord coll, t_ray r, char **map, bool is_horiz);
double get_vert_coll(t_player p, t_ray r, char **map);
int check_dir(t_ray r, bool is_horiz);
double deg_to_rad(double degrees);
double radians_to_degrees(double radians) ;
double norm_angle(double angle);

double *cast_rays(char **map, t_player p)
{
	int i;
	t_ray r;
	double *distances;

	i = 0;
	r.pos = p.pos;
	distances = malloc(sizeof(double) * WINDOW_WIDTH);
	while(i < WINDOW_WIDTH)
	{
		r.dir = p.dir - (FOV / 2) + (FOV / WINDOW_WIDTH) * i;
		r.dir = norm_angle(r.dir);
		printf("r.dir: %f\n", radians_to_degrees(r.dir));
		if(get_horiz_coll(p, r, map) < get_vert_coll(p, r, map))
			distances[i] = get_horiz_coll(p, r, map);
		else
			distances[i] = get_vert_coll(p, r, map);
		i++;
		printf("i = %d\n", i);
	}
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		printf("distances[%d]: %f\n", i, distances[i]);
	}
	return distances;
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
	if(coll.x == -1.0 && coll.y == -1.0)
		return INFINITY;
	dist = sqrt(pow(p.pos.x - coll.x, 2) + pow(p.pos.y - coll.y, 2));
	double angle_diff = r.dir - norm_angle(p.dir);
	printf("dist: %f\n", dist);
    // Print debug information
    printf("r.dir: %f, p.dir: %f, angle_diff: %f\n", radians_to_degrees(r.dir), p.dir, angle_diff);

	dist = dist * cos(angle_diff);
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

void print_map(char **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == WALL) {
                printf("#"); // Print a symbol for the wall
            } else if (map[i][j] == EMPTY) {
                printf(" "); // Print a space for empty cells
            } else {
                printf("%c", map[i][j]); // Print any other characters as they are
            }
        }
        printf("\n");
    }
}

t_coord get_wall_coll(t_coord coll, t_ray r, char **map, bool is_horiz)
{
	t_coord delta;
	int map_x;
	int map_y;

	map_x = ((int)floor((coll.x/CUBE_SIZE)));
	map_y = ((int)floor((coll.y/CUBE_SIZE)));

	delta = get_ray_delta(r, is_horiz);
	print_map(map, 5, 5);
	while(!(map_x < 0 || map_y < 0 || map_x >= 5 || map_y >= 5))
	{
		if(map[map_y][map_x] == WALL)
			return coll;
		coll.x += delta.x;
		coll.y += delta.y;
		map_x = ((int)floor((coll.x/CUBE_SIZE)));
		map_y = ((int)floor((coll.y/CUBE_SIZE)));
		
	}
	return (t_coord){-1.0, -1.0};
	printf("coll.x: %d, coll.y: %d\n", map_x, map_y);
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
		coll.y = floor(p.pos.y/CUBE_SIZE) * CUBE_SIZE - 1; // inside current square
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



