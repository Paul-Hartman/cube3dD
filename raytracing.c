#include "cube3d.h"

t_vars	init(char *file)
{

	vars.mlx = mlx_init();
	malloc_protection(vars.mlx, MLX_INIT_ERROR);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth, vars.screenheight
			+ (CHAR_HEIGHT * 2), "so_long");
	malloc_protection(vars.win, MLX_WINDOW_ERROR);
	return (vars);
}
