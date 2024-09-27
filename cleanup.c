/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:03:53 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 18:10:42 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.c>

void	cleanup(t_data *data)
{
	if (data->map)
		free_map(data->map);
	if (data->mlx_ptr != NULL)
	{
		if (data->win_ptr != NULL)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}
