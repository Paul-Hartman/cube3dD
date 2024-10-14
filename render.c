/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/14 18:31:52 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	put_pixel_from_img(t_data *data, t_image *src_img,
	t_coord src_coord, t_coord dest_coord)
{
	char	*pixel_src;
	char	*pixel_dest;
	int		offset_dest;
	int		offset_src;


	offset_dest = dest_coord.y * data->lsize + dest_coord.x * data->bpp / 8;
	pixel_dest = data->imgbuff + offset_dest;

	src_coord.x = (int)src_coord.x;
	src_coord.y = (int)src_coord.y;

	offset_src = src_coord.y * src_img->lsize + src_coord.x * src_img->bpp / 8;
	pixel_src = src_img->buff + offset_src;
	ft_memcpy(pixel_dest, pixel_src, 4);
}

void	render_frame(t_data *data)
{
	t_ray	*rays;
	
	rays = cast_rays(data->map, *data->player);
	if (currtime() - data->last_render > MS_BETWEEN_FRAMES)
	{
		draw_walls(rays, data);
		draw_minimap(data, rays);
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img_ptr, 0, 0);
		data->last_render = currtime();
	}
}

void	draw_square(t_data *data, t_coord pos, int size, int c[3])
{
	int	i;
	int	j;
	i = 0;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			set_pixel(data, c, pos.x + i, pos.y + j);
			j++;
		}
		i++;
	}
}

void draw_line(t_data *data, t_coord p1, t_coord p2)
{
	int distx;
	int disty;
	int stepx;
	int stepy;
	int err;
	distx = abs((int)p2.x - (int)p1.x);
	disty = abs((int)p2.y - (int)p1.y);
	err = distx - disty;
	if(p1.x < p2.x)
		stepx = 1;
	else
		stepx = -1;
	if(p1.y < p2.y)
		stepy = 1;
	else
		stepy = -1;
	while (p1.x < data->map->width * MINI_TILE_SZ && p1.y < data->map->height * MINI_TILE_SZ && p1.x >= 0 && p1.y >= 0)
	{

		if (p1.x < p2.x)
			p1.x++;
		else if (p1.x > p2.x)
			p1.x--;
		if (p1.y < p2.y)
			p1.y++;
		else if (p1.y > p2.y)
			p1.y--;
		set_pixel(data, (int[3]){255, 255, 255}, (int)p1.x, (int)p1.y);
		if (fabs(p1.x - p2.x) < 2 && fabs(p1.y - p2.y) < 2)
			break;
		if(2 * err > -disty)
		{
			p1.x += stepx;
			err -= disty;
		}
		if(2 * err < distx)
		{
			p1.y += stepy;
			err += distx;
		}
	}
}

void draw_player(t_data *data, t_ray *rays)
{
	t_coord p;
	t_coord end_line;
	int i;
	i=0;
	
	p.x = data->player->pos.x / CUBE_SIZE * MINI_TILE_SZ;
	p.y = data->player->pos.y / CUBE_SIZE * MINI_TILE_SZ;
	draw_square(data, p, 5, (int[3]){0, 255, 0});
	while(i < WINDOW_WIDTH)
	{
		if (i % 20 == 0)
		{
			end_line.x = rays[i].coll.x / CUBE_SIZE * MINI_TILE_SZ;
			end_line.y = rays[i].coll.y / CUBE_SIZE * MINI_TILE_SZ;
			draw_line(data, p, end_line);
		}
		i++;	
	}
}

void	draw_minimap(t_data *data, t_ray *rays)
{
	int	y;
	int	x;
	int y_offset;
	int x_offset;
	
	y_offset = (data->player->pos.y/ CUBE_SIZE)*MINI_TILE_SZ - MINI_SIZE / 2;
	x_offset = (data->player->pos.x/ CUBE_SIZE)* MINI_TILE_SZ - MINI_SIZE / 2;
	if (y_offset < 0)
		y_offset = 0;
	if (x_offset < 0)
		x_offset = 0;
	y = y_offset;
	while (y/MINI_TILE_SZ < data->map->height && y< MINI_SIZE)
	{
		x = x_offset;
		while (x/MINI_TILE_SZ  < data->map->width && x < MINI_SIZE)
		{
			if (data->map->grid[y/ CUBE_SIZE][x/ CUBE_SIZE] == WALL)
				draw_square(data, (t_coord){x, y},MINI_TILE_SZ, (int[3]){95, 95, 95});
			else
				draw_square(data, (t_coord){x, y}, MINI_TILE_SZ, (int[3]){195, 195, 195});
			x++;
		}
		y++;
	}
	draw_player(data, rays);
}

