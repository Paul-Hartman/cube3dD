/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:29:21 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:01 by wpepping         ###   ########.fr       */
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
	init_data(data);
	init_map(data->map);
	init_trig_tables(data->sin_table, data->cos_table);
	init_textures(data->textures);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (err_handl(OOM_ERROR, data));
	if (read_map(data, fname) < 0)
		return (err_handl(MAP_ERROR, data));
	if (init_doors(data->map) < 0)
		return (err_handl(OOM_ERROR, data));
	if (init_window(data) < 0)
		return (err_handl(OOM_ERROR, data));
	return (0);
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
