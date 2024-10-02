/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:22 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/02 18:54:33 by wpepping         ###   ########.fr       */
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

void	put_pixel_from_img(t_data *data, t_image *src_img,
	t_coord src_coord, t_coord dest_coord)
{
	char	*pixel_src;
	char	*pixel_dest;
	int		offset;

	offset = dest_coord.y * data->lsize + dest_coord.x * data->bpp / 8;
	pixel_src = data->imgbuff + offset;
	offset = src_coord.y * src_img->lsize + src_coord.x * src_img->bpp / 8;
	offset = offset % (src_img->lsize * TEXTURE_HEIGHT);
	pixel_dest = src_img->buff + offset;
	ft_memcpy(pixel_dest, pixel_src, 4);
}

void	move_player(t_data *data, int x, int y)
{
	(void)data;
	(void)x;
	(void)y;
	return ;
}

