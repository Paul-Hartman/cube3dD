/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/21 18:33:41 by wpepping         ###   ########.fr       */
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
	int		offset;

	offset = src_coord.y * src_img->lsize + src_coord.x * src_img->bpp / 8;
	pixel_src = src_img->buff + offset;
	if (pixel_src[3] == -1)
		return ;
	offset = dest_coord.y * data->lsize + dest_coord.x * data->bpp / 8;
	pixel_dest = data->imgbuff + offset;
	ft_memcpy(pixel_dest, pixel_src, 4);
}


void update_enemy_frame(t_enemy *enemy)
{
	double current_time = currtime();

	if (current_time - enemy->last_frame_time >= MS_BETWEEN_FRAMES *10)
	{
		if (enemy->state == ATTACK)
			enemy->frame = 0 + (enemy->frame + 1) % 4;
		else if (enemy->state == WALK)
			enemy->frame = 4 + (enemy->frame + 1 - 4) % 4;
		else if (enemy->state == DIE)
			enemy->frame = 8 + (enemy->frame + 1 - 8) % 3;
		enemy->last_frame_time = current_time;
	}
}


int render_sprites(t_data *data, t_ray *rays)
{
	t_sprite	*sprite;
	t_sprite enemy_sprite = ((t_sprite){data->enemy->pos, data->enemy->height, data->enemy->width, true, false, NULL});

	update_enemy_frame(data->enemy);
	sprite = get_sprite_coll(data, rays, &enemy_sprite);
	if (sprite != NULL)
		put_sprite(data, sprite);
	else
		return(0);
	return (1);
}

void	draw_gun(t_data *data)
{
	int	img_start_x;
	int	img_start_y;
	int	i;
	int	j;

	img_start_x = (WINDOW_WIDTH - GUN_WIDTH) / 2;
	img_start_y = WINDOW_HEIGHT - GUN_HEIGHT;
	i = 0;
	j = 0;
	while (i < GUN_HEIGHT)
	{
		j = 0;
		while (j < GUN_WIDTH)
		{
			(void)data;
			put_pixel_from_img(data, &data->textures->gun[0],
				(t_coord){j, i}, (t_coord){img_start_x + j, img_start_y + i});
			j++;
		}
		i++;
	}
}

void	render_frame(t_data *data)
{
	t_ray	*rays;

	rays = cast_rays(data->map, *data->player);
	if (currtime() - data->last_render > MS_BETWEEN_FRAMES)
	{
		draw_walls(rays, data);
		draw_minimap(data, rays);
		render_sprites(data, rays);
		data->last_render = currtime();
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img_ptr, 0, 0);
		draw_gun(data);
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

void draw_player(t_data *data, t_ray *rays, t_coord offset)
{
	t_coord p;
	t_coord e;
	t_coord end_line;
	int i;
	i=0;

	p.x = data->player->pos.x / CUBE_SIZE * MINI_TILE_SZ - offset.x;
	p.y = data->player->pos.y / CUBE_SIZE * MINI_TILE_SZ - offset.y;
	e.x = data->enemy->pos.x / CUBE_SIZE * MINI_TILE_SZ - offset.x;
	e.y = data->enemy->pos.y / CUBE_SIZE * MINI_TILE_SZ - offset.y;
	draw_square(data, (t_coord){p.x - 2.5, p.y - 2.5}, 5, (int[3]){0, 255, 0});

	while(i < WINDOW_WIDTH)
	{
		if (i % 20 == 0 && i !=0)
		{
			end_line.x = rays[i].coll.x / CUBE_SIZE * MINI_TILE_SZ - offset.x;
			end_line.y = rays[i].coll.y / CUBE_SIZE * MINI_TILE_SZ - offset.y;
			if(end_line.x > MINI_SIZE)
				end_line.x = MINI_SIZE + MINI_TILE_SZ;
			if(end_line.y > MINI_SIZE)
				end_line.y = MINI_SIZE + MINI_TILE_SZ;
            draw_line(data, p, end_line);
		}
		i++;
	}
	draw_square(data, (t_coord){e.x - 2.5, e.y - 2.5}, 5, (int[3]){255, 0, 0});
}

void	draw_minimap(t_data *data, t_ray *rays)
{
	int	y;
	int	x;
	t_coord offset;


	offset.y = (data->player->pos.y/ CUBE_SIZE)*MINI_TILE_SZ - MINI_SIZE / 2;
	offset.x = (data->player->pos.x/ CUBE_SIZE)* MINI_TILE_SZ - MINI_SIZE / 2;
	offset.y = max(offset.y, 0);
	offset.x = max(offset.x, 0);
	y = offset.y;
	while (y / MINI_TILE_SZ < data->map->height && y< MINI_SIZE + offset.y)
	{
		x = offset.x;
		while (x/MINI_TILE_SZ  < data->map->width && x < MINI_SIZE + offset.x)
		{
			if (data->map->grid[y/ MINI_TILE_SZ][x/ MINI_TILE_SZ] == WALL)
				draw_square(data, (t_coord){x- offset.x, y - offset.y},MINI_TILE_SZ, (int[3]){95, 95, 95});
			else if (data->map->grid[y/ MINI_TILE_SZ][x/ MINI_TILE_SZ] != SPACE)
				draw_square(data, (t_coord){x- offset.x, y - offset.y}, MINI_TILE_SZ, (int[3]){195, 195, 195});
			x += MINI_TILE_SZ/5;
		}
		y+= MINI_TILE_SZ/5;
	}


	draw_player(data, rays, offset);
}
