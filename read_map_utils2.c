/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:53 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/15 20:01:30 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->floor = NULL;
	config->ceiling = NULL;
	config->door = NULL;
	config->north = NULL;
	config->east = NULL;
	config->south = NULL;
	config->west = NULL;
	config->map_start = 0;
}
