/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:29:48 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/18 15:45:51 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_loop(t_data *data)
{
	bool	moved;

	moved = false;
	if (data->key_state.mv_up)
		moved = move_player(data, false) || moved;
	if (data->key_state.mv_dn)
		moved = move_player(data, true) || moved;
	if (data->key_state.mv_r)
		moved = strafe_player(data, false) || moved;
	if (data->key_state.mv_l)
		moved = strafe_player(data, true) || moved;
	if (data->key_state.rot_r)
		moved = rotate_player(data, false, ROTATE_SPEED) || moved;
	if (data->key_state.rot_l)
		moved = rotate_player(data, true, ROTATE_SPEED) || moved;
	if (data->active_door)
		moved = move_door(data, data->active_door) || moved;
	if (move_enemy(data) ||moved)
		render_frame(data);
	
	
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
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		data->key_state.run = true;
	if (keycode == XK_space)
		activate_door(data, get_gridpos_in_front(data->player));
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
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		data->key_state.run = false;
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int	dx;

	(void)y;
	dx = x - WINDOW_WIDTH / 2;
	data->mouse_x = x;
	if (x != WINDOW_WIDTH / 2)
	{
		rotate_player(data, false, MOUSE_SENSITIVITY * dx);
		render_frame(data);
		mlx_mouse_move(data->mlx_ptr, data->win_ptr,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	return (0);
}
