/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:26 by phartman          #+#    #+#             */
/*   Updated: 2024/10/22 15:50:37 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_mouse_click(int button, int x, int y, t_data *data)
{	
	(void)x;
	(void)y;
	if (button == Button1)
		kill_enemy(data, get_gridpos_in_front(data->player));
	return (0);
}