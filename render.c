/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/07 18:47:16 by phartman         ###   ########.fr       */
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
	int		offset_src;
	int		offset_dest;


	offset_dest = dest_coord.y * data->lsize + dest_coord.x * data->bpp / 8;
	pixel_dest = data->imgbuff + offset_dest;

	src_coord.x = (int)src_coord.x;
	src_coord.y = (int)src_coord.y;

	offset_src = src_coord.y * src_img->lsize + src_coord.x * src_img->bpp / 8;
	pixel_src = src_img->buff + offset_src;
	ft_memcpy(pixel_dest, pixel_src, 4);
}

void	draw_square(t_data *data, int x, int y, int c[3])
{
	int	i;
	int	j;

	i = 0;
	x = x * MINI_TILE_SZ;
	y = y * MINI_TILE_SZ;
	while (i < MINI_TILE_SZ)
	{
		j = 0;
		while (j < MINI_TILE_SZ)
		{
			set_pixel(data, c, x + i, y + j);
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
	printf("start\n");
	while(i < WINDOW_WIDTH)
	{
		if (i % 20 == 0)
		{
			end_line.x = rays[i].coll.x / CUBE_SIZE * MINI_TILE_SZ;
			end_line.y = rays[i].coll.y / CUBE_SIZE * MINI_TILE_SZ;
			printf("p.x: %f, p.y: %f, end_line.x: %f, end_line.y: %f\n", p.x, p.y, end_line.x, end_line.y);
			draw_line(data, p, end_line);
		}
		i++;	
	}
	printf("end\n");
}

void	draw_minimap(t_data *data, t_ray *rays)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->grid[y][x] == WALL)
				draw_square(data, x, y, (int[3]){200, 0, 255});
			else
				draw_square(data, x, y, (int[3]){255, 200, 0});
			x++;
		}
		y++;
	}
	draw_player(data, rays);
}

