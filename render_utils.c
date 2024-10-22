#include "cub3d.h"


void	set_pixel(t_data *data, int c[3], int x, int y)
{
	int		color;
	char	*pixel;

	color = (c[0] * 256 * 256 + c[1] * 256 + c[2]);
	color = mlx_get_color_value(data->mlx_ptr, color);
	pixel = data->imgbuff + y * data->lsize + x * data->bpp / 8;
	ft_memcpy(pixel, &color, 4);
}

void	put_pixel_from_img(t_data *data, t_image *src_img, t_coord src_coord,
		t_coord dest_coord)
{
	char	*pixel_src;
	char	*pixel_dest;
	int		offset;

	offset = src_coord.y * src_img->lsize + src_coord.x * src_img->bpp / 8;
	pixel_src = src_img->buff + offset;
	if (pixel_src[3] == -1)
		return ;
	offset = dest_coord.y * data->lsize + dest_coord.x * data->bpp / 8;
	pixel_dest = data->imgbuff + offset;
	ft_memcpy(pixel_dest, pixel_src, 4);
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

int	get_tex_offset(t_ray r)
{
	int	tex_x;

	if (r.is_horiz)
		tex_x = (int)r.coll.x % CUBE_SIZE;
	else
		tex_x = (int)r.coll.y % CUBE_SIZE;

	return (tex_x);
}



