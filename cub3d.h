/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:52:36 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 20:28:05 by wpepping         ###   ########.fr       */
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
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

# define FOV 1.047198 //60 degrees in radians
# define CHAR_HEIGHT 32
# define CUBE_SIZE 64
# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480

# define EMPTY 48
# define WALL 49
# define NORTH 78
# define EAST 69
# define SOUTH 83
# define WEST 87

# define WINDOW_NAME "Cub3d"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*imgbuff;
	char	**map;
	int		map_width;
	int		map_height;
	int		lsize;
	int		bpp;
	int		endian;
}				t_data;

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_ray
{
	t_coord	pos;
	double	dir;
}				t_ray;

typedef struct s_player
{
	t_coord	pos;
	double	dir;
}				t_player;



// typedef struct s_vars
// {
// 	void	*mlx;
// 	void	*win;
// 	int		screenwidth;
// 	int		screenheight;
// }				t_vars;

// raycasting
void cast_rays(char **map, t_player p);

// Read map
int				read_map(t_data *data, char *fname);

// Render
void			set_pixel(t_data *data, int c[3], int x, int y);
void			move_player(t_data *data, int x, int y);

// Events
int				handle_loop(t_data *data);
int				handle_close(t_data *data);
int				handle_input(int keycode, t_data *data);
int				handle_mouse(t_data *data);

// Clean up
void			cleanup(t_data *data);
void			free_map(char **map);

#endif
