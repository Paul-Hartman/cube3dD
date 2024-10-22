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

void	update_enemy_frame(t_enemy *enemy)
{
	double	current_time;

	current_time = currtime();
	if (current_time - enemy->last_frame_time >= MS_BETWEEN_FRAMES * 10)
	{
		if (enemy->state == ATTACK)
			enemy->frame = 0 + (enemy->frame + 1) % 4;
		else if (enemy->state == WALK)
			enemy->frame = 4 + (enemy->frame + 1 - 4) % 4;
		else if (enemy->state == DIE)
		{
			if (enemy->frame < 8)
				enemy->frame = 8;
			else if (enemy->frame >= 8 && enemy->frame < 10)
				enemy->frame++;
		}
		enemy->last_frame_time = current_time;
	}
}

void	render_sprites(t_data *data, t_ray *rays)
{
	int			i;
	t_sprite	*sprite;
	t_sprite	enemy_sprite;

	i = 0;
	while (i < data->nr_of_enemies)
	{
		update_enemy_frame(&data->enemies[i]);
		enemy_sprite = ((t_sprite){data->enemies[i].pos, data->enemies[i].frame,
				data->enemies[i].size, data->enemies[i].size, true, false,
				NULL});
		sprite = get_sprite_coll(data, rays, &enemy_sprite);
		if (sprite != NULL)
			put_sprite(data, sprite);
		i++;
	}
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
			put_pixel_from_img(data, &data->textures->gun[0], (t_coord){j, i},
				(t_coord){img_start_x + j, img_start_y + i});
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
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
		draw_gun(data);
	}
}
