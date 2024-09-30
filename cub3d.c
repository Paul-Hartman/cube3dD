/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:07:30 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/30 16:27:54 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(char *error_msg, t_data *data)
{
	ft_putendl_fd(error_msg, 2);
	cleanup(data);
	return (-1);
}

static int	init(t_data *data, char *map)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map = NULL;
	if (read_map(data, map) < 0)
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

// static void	init_events(t_data *data)
// {
// 	mlx_key_hook(data->win_ptr, &handle_input, data);
// 	mlx_mouse_hook(data->win_ptr, &handle_mouse, data);
// 	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
// 		&handle_close, data);
// }

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

int main(int argc, char **argv)
{
	t_data	data;
	if (check_input(argc, argv) || init(&data, argv[1]))
		return (1);
    t_player player;
	player.pos.x = 3 * CUBE_SIZE;
	player.pos.y = CUBE_SIZE;
	player.dir = 0;
	cast_rays(data.map, player);
	return 0;
}

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	if (check_input(argc, argv) || init(&data, argv[1]))
// 		return (1);
// 	init_events(&data);
// 	//load_textures(&data);
// 	mlx_loop(data.mlx_ptr);
// 	//unload_textures(&data);
// 	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	return (0);
// }
