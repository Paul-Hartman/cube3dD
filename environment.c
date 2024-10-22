
#include "cub3d.h"

void draw_walls(t_data *data, t_ray *rays, int i, int j)
{
	t_coord tex;
	t_image	*texture;
	int		height;
	int		wall_top;

	height = (int)projected_wall_height(data->focal_len, rays[i].dist);
	wall_top = WINDOW_HEIGHT / 2 - height / 2;
	texture = get_texture(data->textures, &rays[i]);
	tex.x = get_tex_offset(rays[i]);
	tex.y = ((j - wall_top) * TEXTURE_HEIGHT) / height;
	put_pixel_from_img(data, texture, tex, (t_coord){i, j});
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
		r.dist = r.dist/ data->cos_table[angle_to_index(r.dir - data->player->dir)];
		r.coll.x = data->player->pos.x + r.dist * data->cos_table[angle_to_index(r.dir)] * 3;
		r.coll.y = data->player->pos.y - r.dist * data->sin_table[angle_to_index(r.dir)] * 3;
		r.coll.x = ((int)(r.coll.x * 1000) % (CUBE_SIZE * 1000)) / 1000.0 / CUBE_SIZE;
		r.coll.y = ((int)(r.coll.y * 1000) % (CUBE_SIZE * 1000)) / 1000.0 / CUBE_SIZE;
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
		r.dist = r.dist/ data->cos_table[angle_to_index(r.dir - data->player->dir)];
		r.coll.x = data->player->pos.x - r.dist * data->cos_table[angle_to_index(r.dir)] * 3;
		r.coll.y = data->player->pos.y + r.dist * data->sin_table[angle_to_index(r.dir)] * 3;
		r.coll.x = ((int)(r.coll.x * 1000) % (CUBE_SIZE * 1000)) / 1000.0 / CUBE_SIZE;
		r.coll.y = ((int)(r.coll.y * 1000) % (CUBE_SIZE * 1000)) / 1000.0 / CUBE_SIZE;
		tex_x = (int)(r.coll.x  * (TEXTURE_HEIGHT));
		tex_y = (int)(r.coll.y  * (TEXTURE_HEIGHT));
		put_pixel_from_img(data, &data->textures->north, (t_coord){tex_x, tex_y}, (t_coord){i, j});
	}
	else
		set_pixel(data, data->ceiling, i, j);
}