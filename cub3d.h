# ifndef CUBE3D_H
#define CUBE3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>

#define FOV 60
#define CHAR_HEIGHT 32
#define WALL_HEIGHT 64

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

#endif