/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:09:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/30 18:45:52 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(void *p, char **map)
{
	if (p != NULL)
		free(p);
	if (map)
		free_map(map);
	return (-1);
}

static char	*get_first_map_line(int fd, int skip_lines)
{
	char	*line;

	while (skip_lines > 0)
	{
		get_next_line(fd);
		skip_lines--;
	}
	line = get_next_line(fd);
	while (line && line[0] == '\n')
		line = get_next_line(fd);
	return (line);
}

static int	is_valid(char *line, int width)
{
	int	len;

	len = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ')
		{
			if (*line != EMPTY && *line != WALL && *line != NORTH
				&& *line != SOUTH && *line != EAST && *line != WEST)
				return (false);
			len++;
		}
		line++;
	}
	if (len != width)
		return (false);
	return (true);
}

int	get_map_dimensions(t_map *map, int fd)
{
	char	*temp;
	char	*line;

	temp = get_first_map_line(fd, 0);
	if (!temp)
		return (-1);
	line = ft_remove(temp, ' ');
	free(temp);
	map->width = ft_strlen(line);
	if (map->width == 0)
		return (err_handl(line, NULL));
	if (line[map->width - 1] == '\n')
		map->width--;
	map->height = 0;
	while (line)
	{
		if (!is_valid(line, map->width))
			return (err_handl(line, NULL));
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	read_map_content(t_map *map, int fd, int map_start)
{
	int		i;
	char	*line;

	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (-1);
	line = get_first_map_line(fd, map_start);
	i = 0;
	while (i < map->height)
	{
		if (!line)
			return (err_handl(NULL, map->grid));
		map->grid[i] = ft_remove(line, ' ');
		map->grid[i][map->width] = '\0';
		free(line);
		line = get_next_line(fd);
		i++;
	}
	get_next_line(fd);
	close(fd);
	return (0);
}
