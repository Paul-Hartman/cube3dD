/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:52:36 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 18:26:05 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

#define FOV 60
#define CAR_HEIGHT 32
#define WALL_HEIGHT 64

typedef enum e_mapchars
{
	WORD,
	HEREDOC,
	APPEND,
	REDIRECT_OUT,
	REDIRECT_IN,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PIPE
}	t_mapchars;

typedef struct s_main {
	char	*imgbuff,
	int		lsize,
	int		bpp,
	int		endian
} 				t_main

typedef struct s_ray
{
	float x;
	float y;
	float dx;
	float dy;

}				t_ray;

typedef struct s_player
{
	float x;
	float y;
	float angle;
}				t_player;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		screenwidth;
	int		screenheight;
}				t_vars;

void			cleanup(t_data *data);

#endif
