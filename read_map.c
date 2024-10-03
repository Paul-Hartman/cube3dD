/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:03:56 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/02 16:35:39 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	err_handl(int fd)
{
	if (fd != -1)
		close(fd);
	return (-1);
}

static int	save_type(t_config *config, int fd, char type[2])
{
	char	value[PATH_MAX + 1];

	read_to_eoln(fd, value);
	if (type[0] == 'F')
		return (try_save(&config->floor, value));
	if (type[0] == 'C')
		return (try_save(&config->ceiling, value));
	if (type[0] == 'N' && type[1] == 'O')
		return (try_save(&config->north, value));
	if (type[0] == 'E' && type[1] == 'A')
		return (try_save(&config->east, value));
	if (type[0] == 'S' && type[1] == 'O')
		return (try_save(&config->south, value));
	if (type[0] == 'W' && type[1] == 'E')
		return (try_save(&config->west, value));
	return (-1);
}

static int	read_type(int fd, char type[2])
{
	int		bytes_read;
	int		lines_read;
	char	c;

	lines_read = 1;
	bytes_read = read(fd, &type[0], 1);
	while (bytes_read && type[0] == '\n')
	{
		lines_read++;
		bytes_read = read(fd, &type[0], 1);
	}
	if (!bytes_read)
		return (-1);
	if (type[0] != 'F' && type[0] != 'C')
		read(fd, &type[1], 1);
	bytes_read = read(fd, &c, 1);
	if (bytes_read == 0 || c != ' ')
		return (-1);
	return (lines_read);
}

static int	read_config(t_config *config, int fd)
{
	int		i;
	int		lines;
	char	type[2];

	config->floor = NULL;
	config->ceiling = NULL;
	config->north = NULL;
	config->east = NULL;
	config->south = NULL;
	config->west = NULL;
	config->map_start = 0;
	i = 0;
	while (i < 6)
	{
		lines = read_type(fd, type);
		if (lines < 0)
			return (-1);
		config->map_start += lines;
		if (save_type(config, fd, type) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	read_map(t_data *data, char *fname)
{
	int			fd;
	t_config	config;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read_config(&config, fd) < 0)
		return (err_handl(fd));
	load_textures(data, &config);
	if (save_rgbs(config.floor, data->floor) < 0)
		return (err_handl(fd));
	if (save_rgbs(config.ceiling, data->ceiling) < 0)
		return (err_handl(fd));
	if (get_map_dimensions(data->map, fd) < 0)
		return (err_handl(fd));
	close(fd);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (read_map_content(data->map, fd, config.map_start));
}
