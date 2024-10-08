/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:07:36 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/07 17:30:18 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_loop(t_data *data)
{
	bool	moved;

	moved = false;
	if (data->key_state.mv_up)
		moved = move_player(data, false);
	if (data->key_state.mv_dn)
		moved = move_player(data, true);
	if (data->key_state.mv_r)
		moved = strafe_player(data, false);
	if (data->key_state.mv_l)
		moved = strafe_player(data, true);
	if (data->key_state.rot_r)
		moved = rotate_player(data, false, ROTATE_SPEED);
	if (data->key_state.rot_l)
		moved = rotate_player(data, true, ROTATE_SPEED);
	if (moved)
	{
		draw_walls(cast_rays(data->map, *data->player), data);
		draw_minimap(data);
		//draw_line(data, (t_coord){10 ,10}, (t_coord){100, 100});
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img_ptr, 0, 0);
	}
	return (0);
}

int	handle_close(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

// int	handle_input(int keycode, t_data *data)
// {
// 	if (keycode == XK_Escape)
// 		mlx_loop_end(data->mlx_ptr);
// 	if (keycode == XK_w || keycode == XK_W || keycode == XK_Up)
// 		move_player(data, false);
// 	if (keycode == XK_s || keycode == XK_S || keycode == XK_Down)
// 		move_player(data, true);
// 	if (keycode == XK_a || keycode == XK_A || keycode == XK_Left)
// 		rotate_player(data, -0.1);
// 	if (keycode == XK_d || keycode == XK_D || keycode == XK_Right)
// 		rotate_player(data, 0.1);
// 	return (0);
// }

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx_ptr);
	if (keycode == XK_w || keycode == XK_W || keycode == XK_Up)
		data->key_state.mv_up = true;
	if (keycode == XK_s || keycode == XK_S || keycode == XK_Down)
		data->key_state.mv_dn = true;
	if (keycode == XK_a || keycode == XK_A)
		data->key_state.mv_l = true;
	if (keycode == XK_d || keycode == XK_D)
		data->key_state.mv_r = true;
	if (keycode == XK_Right)
		data->key_state.rot_r = true;
	if (keycode == XK_Left)
		data->key_state.rot_l = true;
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_w || keycode == XK_W || keycode == XK_Up)
		data->key_state.mv_up = false;
	if (keycode == XK_s || keycode == XK_S || keycode == XK_Down)
		data->key_state.mv_dn = false;
	if (keycode == XK_a || keycode == XK_A)
		data->key_state.mv_l = false;
	if (keycode == XK_d || keycode == XK_D)
		data->key_state.mv_r = false;
	if (keycode == XK_Right)
		data->key_state.rot_r = false;
	if (keycode == XK_Left)
		data->key_state.rot_l = false;
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	(void)y;
	if (x != WINDOW_WIDTH / 2)
	{
		rotate_player(data, x < WINDOW_WIDTH / 2, MOUSE_SENSITIVITY);
		draw_walls(cast_rays(data->map, *data->player), data);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img_ptr, 0, 0);
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	return (0);
}
