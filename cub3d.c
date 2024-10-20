/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:29:21 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 17:13:15 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(char *error_msg, t_data *data)
{
	ft_putendl_fd(error_msg, 2);
	cleanup(data);
	return (-1);
}

void init_trig_tables(double *sin_table, double *cos_table)
{
	double angle;
	int i;

	i = 0;
	while (i < 3600)
	{
		angle = deg_to_rad(i * 0.1);
		sin_table[i] = sin(angle);
		cos_table[i] = cos(angle);
		i++;
	}
}

t_enemy *init_enemy(t_data *data)
{

	t_coord	coord;
	t_enemy *enemy;
	enemy = (t_enemy *)malloc(sizeof(t_enemy));

	coord.y = 0;
	while (coord.y < data->map->height)
	{
		coord.x = 0;
		while (coord.x < data->map->width)
		{
			if(data->map->grid[(int)coord.y][(int)coord.x] == ENEMY)
			{
				enemy->x = coord.x;
				enemy->y = coord.y;
				enemy->width = 128;
				enemy->height = 128;
				enemy->pos = (t_coord){coord.x * CUBE_SIZE + 0.5 * CUBE_SIZE, coord.y * CUBE_SIZE + 0.5 * CUBE_SIZE};
				enemy->point_a = (t_coord){enemy->x + 30, enemy->y + 30};
				enemy->point_b = (t_coord){enemy->x + 30, enemy->y + 30};
				enemy->target = data->player->pos;
				enemy->dir = 'E';
				enemy->state = WALK;
				enemy->frame = 0;
				enemy->last_frame_time = currtime();
				return(enemy);
			}
			coord.x++;
		}
		coord.y++;
	}
	return (NULL);
}

static int	init(t_data *data, char *fname)
{
	data->key_state = (t_key_state){0, 0, 0, 0, 0, 0};
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->map->grid = NULL;
	
	init_trig_tables(data->sin_table, data->cos_table);
	init_textures(data->textures);
	data->focal_len = (WINDOW_WIDTH / 2.0) / (tan(FOV / 2.0));
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (err_handl("Out of memory error", data));
	if (read_map(data, fname) < 0)
		return (err_handl(MAP_ERROR, data));
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (data->win_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->imgbuff = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&(data->lsize), &(data->endian));
	data->last_render = currtime();
	data->mouse_x = WINDOW_WIDTH / 2;
	data->enemy = init_enemy(data);
	return (0);
}

static void	init_events(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_key_press, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_key_release, data);
	//mlx_key_hook(data->win_ptr, &handle_input, data);
	//mlx_mouse_hook(data->win_ptr, &handle_mouse, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_close, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
		&handle_mouse_move, data);
	mlx_loop_hook(data->mlx_ptr, &handle_loop, data);
	mlx_mouse_move(data->mlx_ptr, data->win_ptr,
		WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
}

static int	check_input(int argc, char **argv)
{
	if (argc != 2 || ft_strncmp(file_ext(argv[1]), ".cub", 4) != 0)
	{
		ft_putendl_fd("Usage: cub3d <map name>.cub", 2);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_map		map;
	t_player	player;
	t_textures	textures;

	data.map = &map;
	data.player = &player;
	data.textures = &textures;
	if (check_input(argc, argv) < 0 || init(&data, argv[1]) < 0)
		return (1);
	if (find_player(&map, &player) < 0 || !is_valid_map(&map, &player))
	{
		ft_putendl_fd(MAP_ERROR, STDERR_FILENO);
		cleanup(&data);
		return (1);
	}
	init_events(&data);
	draw_walls(cast_rays(data.map, *data.player), &data);
	draw_minimap(&data, cast_rays(data.map, *data.player));
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	cleanup(&data);
	return (0);
}
