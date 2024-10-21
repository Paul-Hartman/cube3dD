/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:58:17 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/18 15:59:51 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	get_gridpos_in_front(t_player *player)
{
	int	player_dir;

	player_dir = get_dir(player->dir);
	if (player_dir == NORTH)
		return (coord_add(pixel2grid(player->pos), (t_coord){0, -1}));
	if (player_dir == EAST)
		return (coord_add(pixel2grid(player->pos), (t_coord){1, 0}));
	if (player_dir == SOUTH)
		return (coord_add(pixel2grid(player->pos), (t_coord){0, 1}));
	if (player_dir == WEST)
		return (coord_add(pixel2grid(player->pos), (t_coord){-1, 0}));
	return ((t_coord){-1, -1});
}

int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}
