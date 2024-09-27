/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:05:27 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 18:05:52 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_loop(t_data *data)
{
	return (0);
}

int	handle_close(t_data *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

int	handle_input(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx);
	if (keycode == XK_w || keycode == XK_W || keycode == XK_Up)
		move_player(data, 0, -1);
	if (keycode == XK_s || keycode == XK_S || keycode == XK_Down)
		move_player(data, 0, 1);
	if (keycode == XK_a || keycode == XK_A || keycode == XK_Left)
		move_player(data, -1, 0);
	if (keycode == XK_d || keycode == XK_D || keycode == XK_Right)
		move_player(data, 1, 0);
	return (0);
}
