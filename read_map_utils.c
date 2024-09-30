/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:28:35 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/30 14:17:52 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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

int	save_floor_ceiling(t_data *data, t_config *config)
{
	(void)data;
	(void)config;
	return (0);
}
