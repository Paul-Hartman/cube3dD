/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:09:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 20:26:50 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

static int	err_handl(int fd, void *p, char **map)
{
	if (fd != -1)
		close (fd);
	if (p != NULL)
		free(p);
	if (map)
		free_map(map);
	return (-1);
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

static int	get_map_dimensions(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	data->map_width = ft_strlen(line);
	if (line[data->map_width - 1] == '\n')
		data->map_width--;
	data->map_height = 0;
	while (line)
	{
		if (!is_valid(line, data->map_width))
			return (err_handl(-1, line, NULL));
		data->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	read_map(t_data *data, char *fname)
{
	int		fd;
	int		i;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (get_map_dimensions(fd, data) < 0)
		return (err_handl(fd, NULL, NULL));
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	close(fd);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = -1;
	while (++i < data->map_height)
	{
		data->map[i] = get_next_line(fd);
		data->map[i][data->map_width] = '\0';
		if (!data->map[i])
			return (err_handl(fd, NULL, data->map));
	}
	get_next_line(fd);
	close(fd);
	return (0);
}
