/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:26 by phartman          #+#    #+#             */
/*   Updated: 2024/10/23 19:01:59 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_click(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == Button1)
		kill_enemy(data, get_gridpos_in_front(data->player));
	if (!data->player->is_shooting)
	{
		data->player->is_shooting = true;
		data->player->gun_last_updated = currtime();
	}
	return (0);
}
