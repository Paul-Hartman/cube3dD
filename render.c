/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/01 16:10:41 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(t_data *data, int c[3], int x, int y)
{
	int		color;
	char	*pixel;

	color = (c[0] * 256 * 256 + c[1] * 256 + c[2]);
	color = mlx_get_color_value(data->mlx_ptr, color);
	pixel = data->imgbuff + y * data->lsize + x * data->bpp / 8;
	ft_memcpy(pixel, &color, 4);
}

void	move_player(t_data *data, int x, int y)
{
	double move_x;
	double move_y;
	
	move_x = x * cos(data->player->dir);
	move_y = y * cos(data->player->dir);
	data->player->pos.x += move_x;
	data->player->pos.y += move_y;
	return ;
}

void	rotate_player(t_data *data, double angle)
{
	data->player->dir += angle;
	data->player->dir = norm_angle(data->player->dir);
	return ;
}

