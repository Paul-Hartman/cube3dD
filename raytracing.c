#include "cub3d.h"

t_vars	init(void)
{
	t_vars vars;

	vars.screenwidth = 1920;
    vars.screenheight = 1080;
	vars.mlx = mlx_init();
	//malloc_protection(vars.mlx, MLX_INIT_ERROR);
	vars.win = mlx_new_window(vars.mlx, vars.screenwidth, vars.screenheight, "cube3D");
	//malloc_protection(vars.win, MLX_WINDOW_ERROR);
	return (vars);
}



int main(int argc, char const *argv[])
{
	
	init();
	return 0;
}
