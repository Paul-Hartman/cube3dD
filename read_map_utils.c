/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:28:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/02 16:48:17 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	save_rgb(char *str, int *dest)
{
	int	strlen;

	strlen = ft_strlen(str);
	if (strlen == 0 || strlen > 3 || !ft_isnum(str))
		return (-1);
	*dest = ft_atoi(str);
	if (*dest > 255)
		return (-1);
	return (0);
}

int	save_rgbs(char *str, int dest[3])
{
	char	**rgb;

	(void)dest;
	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3]
		|| save_rgb(rgb[0], &dest[0]) == -1
		|| save_rgb(rgb[1], &dest[1]) == -1
		|| save_rgb(rgb[2], &dest[2]) == -1)
	{
		free(rgb);
		return (-1);
	}
	free(rgb);
	return (0);
}

int	read_to_eoln(int fd, char *value)
{
	char	c;
	int		i;
	int		bytes_read;

	i = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read && c == ' ')
		bytes_read = read(fd, &c, 1);
	while (bytes_read && i < PATH_MAX && c != '\n')
	{
		value[i] = c;
		i++;
		bytes_read = read(fd, &c, 1);
	}
	if (i == 0 || i == PATH_MAX)
		return (-1);
	value[i] = '\0';
	return (0);
}

int	try_save(char **dest, char *src)
{
	if (*dest)
		return (-1);
	*dest = ft_strdup(src);
	return (0);
}

int	find_player(t_map *map, t_player *player)
{
	t_coord	coord;
	int		n;
	char	c;

	coord.y = 0;
	n = -1;
	while (coord.y < map->height)
	{
		coord.x = 0;
		while (coord.x < map->width)
		{
			c = map->grid[(int)coord.y][(int)coord.x];
			if (c == NORTH || c == EAST || c == SOUTH || c == WEST)
			{
				if (n++ > -1)
					return (-1);
				player->pos.x = coord.x * CUBE_SIZE + 0.5 * CUBE_SIZE;
				player->pos.y = coord.y * CUBE_SIZE + 0.5 * CUBE_SIZE;
				player->dir = get_angle(c);
			}
			coord.x++;
		}
		coord.y++;
	}
	return (n);
}
