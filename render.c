/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/04 18:13:53 by phartman         ###   ########.fr       */
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

	src_coord.x = (int)src_coord.x % src_img->lsize;
	src_coord.y = (int)src_coord.y % src_img->lsize;

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
	int dist;
	dist = (int)sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	while (dist && (p1.x < WINDOW_WIDTH && p1.y < WINDOW_HEIGHT))
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
		dist--;
	}
}

// void draw_player(t_data data)
// {

// }

void	draw_minimap(t_data *data)
{
	int		y;
	int		x;
	t_coord	p;

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
	p.x = data->player->pos.x / CUBE_SIZE * MINI_TILE_SZ;
	p.y = data->player->pos.y / CUBE_SIZE * MINI_TILE_SZ;
	
	//draw_line(data, (t_coord){p.x - 10/2, p.y - 10}, p);
	draw_line(data, (t_coord){p.x + 10/2, p.y - 10}, p);
	set_pixel(data, (int[3]){0, 0, 0}, p.x, p.y);
	
}

