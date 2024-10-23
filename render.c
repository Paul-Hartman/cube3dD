/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/23 16:18:50 by wpepping         ###   ########.fr       */
=======
/*   Updated: 2024/10/23 18:13:00 by phartman         ###   ########.fr       */
>>>>>>> c142046e610a2943e6371a728c65fb59281c4806
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_gun(t_data *data);
static void	render_sprites(t_data *data, t_ray *rays);
static void	draw_env(t_ray *rays, t_data *data);
static void	draw_healthbar(t_data *data);

void	render_frame(t_data *data)
{
	t_ray	*rays;

<<<<<<< HEAD
	if (currtime() - data->last_render > MS_BETWEEN_FRAMES)
=======
	rays = cast_rays(data->map, *data->player);
	if (currtime() - data->last_render > MS_BETWEEN_FRAMES
		&& data->game_state == PLAYING)
>>>>>>> c142046e610a2943e6371a728c65fb59281c4806
	{
		rays = cast_rays(data->map, *data->player);
		draw_env(rays, data);
		draw_minimap(data, rays);
		render_sprites(data, rays);
		data->last_render = currtime();
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
		if (BONUS)
		{
			draw_healthbar(data);
			draw_gun(data);
		}
		free(rays);
	}
	if (data->game_state == GAME_OVER)
	{
		draw_gameover(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0,
			0);
	}
}

static void	draw_env(t_ray *rays, t_data *data)
{
	int	i;
	int	j;
	int	height;
	int	wall_top;

	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		height = (int)projected_wall_height(data->focal_len, rays[i].dist);
		wall_top = WINDOW_HEIGHT / 2 - height / 2;
		j = 0;
		while (j < wall_top && j < WINDOW_HEIGHT)
			draw_ceiling(data, i, j++, data->textures->ceiling.img_ptr != NULL);
		while (j < wall_top + height && j < WINDOW_HEIGHT)
			draw_walls(data, rays, i, j++);
		while (j >= wall_top + height && j < WINDOW_HEIGHT)
			draw_floor(data, i, j++, data->textures->floor.img_ptr != NULL);
	}
}

static void	render_sprites(t_data *data, t_ray *rays)
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

static void	draw_healthbar(t_data *data)
{
	int	img_start_x;
	int	img_start_y;
	int	i;
	int	j;
	int	health;

	health = data->player->health;
	img_start_x = WINDOW_WIDTH - HEALTHBAR_WIDTH;
	img_start_y = 10;
	i = 0;
	j = 0;
	while (i < HEALTHBAR_HEIGHT)
	{
		j = 0;
		while (j < HEALTHBAR_HEIGHT)
		{
			put_pixel_from_img(data, &data->textures->healthbar[health - 1],
				(t_coord){j, i}, (t_coord){img_start_x + j, img_start_y + i});
			j++;
		}
		i++;
	}
}

static void	draw_gun(t_data *data)
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
			put_pixel_from_img(data,
				&data->textures->gun[data->player->gun_texture], (t_coord){j,
				i}, (t_coord){img_start_x + j, img_start_y + i});
			j++;
		}
		i++;
	}
}
