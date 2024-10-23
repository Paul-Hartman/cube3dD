/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:12:35 by phartman          #+#    #+#             */
/*   Updated: 2024/10/23 17:18:11 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	heal(t_data *data);

void	set_game_state(t_data *data)
{
	if (data->player->health == 0)
		data->game_state = GAME_OVER;
	heal(data);
}

static void	heal(t_data *data)
{
	int i;
	bool being_attacked;
	static double last_healed;
	double current_time;

	current_time = currtime();

	being_attacked = false;
	i = -1;
	while (++i < data->nr_of_enemies)
	{
		if (data->enemies[i].state == ATTACK)
		{
			being_attacked = true;
			break ;
		}
	}
	if (current_time - last_healed >= 5000 && !being_attacked)
	{
		if (data->player->health < 9)
			data->player->health++;
		last_healed = current_time;
	}
}