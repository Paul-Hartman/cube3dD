/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:09:39 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/28 22:45:27 by wpepping         ###   ########.fr       */
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

static char	*get_first_map_line(int fd)
{
	char	*line;

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

int	get_map_dimensions(t_data *data, int fd)
{
	char	*line;

	line = get_first_map_line(fd);
	if (!line)
		return (-1);
	data->map_width = ft_strlen(line);
	if (line[data->map_width - 1] == '\n')
		data->map_width--;
	data->map_height = 0;
	while (line)
	{
		if (!is_valid(line, data->map_width))
			return (err_handl(line, NULL));
		data->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	read_map_content(t_data *data, int fd)
{
	int		i;
	char	*line;

	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		return (-1);
	line = get_first_map_line(fd);
	i = 0;
	while (i < data->map_height)
	{
		if (!line)
			return (err_handl(NULL, data->map));
		line[data->map_width] = '\0';
		data->map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	get_next_line(fd);
	close(fd);
	return (0);
}
