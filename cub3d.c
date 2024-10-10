/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:55:11 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/10 13:00:53 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(char *error_msg, t_data *data)
{
	ft_putendl_fd(error_msg, 2);
	cleanup(data);
	return (-1);
}

static int	init(t_data *data, char *fname)
{
	data->key_state = (t_key_state){0, 0, 0, 0, 0, 0};
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->map->grid = NULL;
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
	char	*extension;

	if (argc != 2 || ft_strlen(argv[1]) < 5)
	{
		ft_putendl_fd("Usage: cub3d <map name>.cub", 2);
		return (-1);
	}
	extension = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strncmp(extension, ".cub", 4) != 0)
	{
		free(extension);
		ft_putendl_fd("Usage: cub3d <map name>.cub", 2);
		return (-1);
	}
	free(extension);
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
	draw_minimap(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	cleanup(&data);
	return (0);
}
