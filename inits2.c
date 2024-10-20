/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:44:03 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/18 15:19:24 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_textures *textures)
{
	int i;
	i = 0;
	while (i < 11)
		textures->enemy[i++].img_ptr = NULL;
	textures->north.img_ptr = NULL;
	textures->east.img_ptr = NULL;
	textures->south.img_ptr = NULL;
	textures->west.img_ptr = NULL;
	textures->floor.img_ptr = NULL;
	textures->ceiling.img_ptr = NULL;
	textures->door.img_ptr = NULL;
}

void	init_trig_tables(double *sin_table, double *cos_table)
{
	double	angle;
	int		i;

	i = 0;
	while (i < 3600)
	{
		angle = deg_to_rad(i * 0.1);
		sin_table[i] = sin(angle);
		cos_table[i] = cos(angle);
		i++;
	}
}

static int	nr_of_doors(t_map *map)
{
	int	i;
	int	j;
	int	result;

	result = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == DOOR)
				result++;
		i++;
	}
	return (result);
}

int	init_doors(t_map *map)
{
	int	i;
	int	j;
	int	n;

	map->nr_of_doors = nr_of_doors(map);
	if (map->nr_of_doors != 0)
	{
		map->doors = malloc(map->nr_of_doors * sizeof(t_door));
		if (map->doors == NULL)
			return (-1);
	}
	n = 0;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
			if (map->grid[j++][i] == DOOR)
				map->doors[n++] = (t_door){(t_coord){i, j - 1}, IDLE, 0, 0};
		i++;
	}
	return (0);
}

int init_enemys(t_data *data)
{

	t_coord	coord;
	t_enemy *enemy;
	enemy = (t_enemy *)malloc(sizeof(t_enemy));
	if (!enemy)
		return (-1);
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
				data->enemy = enemy;
			}
			coord.x++;
		}
		coord.y++;
	}
	return (0);
}

