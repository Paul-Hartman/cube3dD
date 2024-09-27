/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:25:52 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 18:05:07 by wpepping         ###   ########.fr       */
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
	if (read_map(data, map) == 0 || check_map(data) == 0)
		return (err_handl("Map error", data));
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height,
			"So long");
	if (data->win_ptr == NULL)
		return (err_handl("Out of memory error", data));
	data->image = mlx_new_image(data->mlx, X, Y);
	if (data->image == NULL)
		return (err_handl("Out of memory error", data));
	data->imgbuff = mlx_get_data_addr(data->image, &data->bpp,
			&(data->lsize), &(data->endian));
	return (0);
}

static void	init_events(t_data *data)
{
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_mouse_hook(data->window, &handle_zoom, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
		&handle_close, data);
}

static int	check_input(int argc, char **argv)
{
	int		strlen;
	char	*extension;

	if (argc != 2 || ft_strlen(argv[1]) < 5)
	{
		ft_putendl_fd("Usage: cub3d <map name>.cub", 2);
		return (-1);
	}
	extension = ft_substr(argv[1], ft_strlen(argv[1]), 4);
	if (ft_strncmp(extension, ".ber", 4) != 0)
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
	t_data	data;

	if (check_input(argc, argv) || init(&data, argv[1]))
		return (1);
	load_textures(&data);
	draw_map(&data);
	mlx_loop(data.mlx_ptr);
	unload_textures(&data);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
