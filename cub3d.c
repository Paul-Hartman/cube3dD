/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:55:11 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/01 12:54:08 by phartman         ###   ########.fr       */
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
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map->grid = NULL;
	if (read_map(data, fname) < 0)
		return (err_handl("Map error", data));
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_NAME);
	if (data->win_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->img_ptr = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->imgbuff = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&(data->lsize), &(data->endian));
	return (0);
}

static void	init_events(t_data *data)
{
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_mouse_hook(data->win_ptr, &handle_mouse, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_close, data);
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

	data.map = &map;
	data.player = &player;
	if (check_input(argc, argv) < 0 || init(&data, argv[1]) < 0)
		return (1);
	if (find_player(&map, &player) < 0 || !is_valid_map(&map, &player))
		return (err_handl("Map error", &data));
 	init_events(&data);
	
	mlx_loop_hook(data.mlx_ptr, handle_loop, &data);
	mlx_loop(data.mlx_ptr);
	
	//unload_textures(&data);
	cleanup(&data);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	if (check_input(argc, argv) || init(&data, argv[1]))
// 		return (1);
// 	init_events(&data);
// 	mlx_loop(data.mlx_ptr);
// 	//unload_textures(&data);
// 	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }
