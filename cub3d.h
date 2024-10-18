/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:13:31 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/18 14:44:48 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include <stdbool.h>
# include "ft_printf/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include "get_next_line.h"
# include "mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <linux/limits.h>
# include <sys/time.h>

# define FOV 1.047198 //60 degrees in radians
//# define FOCAL_LEN 277
# define MINI_TILE_SZ 20
# define MINI_SIZE 250
# define CHAR_HEIGHT 32
# define CUBE_SIZE 180
# define TEXTURE_HEIGHT 180
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 640
# define MOVE_SPEED 0.2
# define MOUSE_SENSITIVITY 0.001
# define ROTATE_SPEED 0.02
# define MS_BETWEEN_FRAMES 10
# define DOOR_STEP 5
# define EPSILON 1e-6
# define M_PI 3.14159265358979323846
# define WINDOW_NAME "Cub3d"
# define MAP_ERROR "Map error"
# define OOM_ERROR "Out of memory error"

# define EMPTY 48
# define WALL 49
# define NORTH 78
# define EAST 69
# define SOUTH 83
# define WEST 87
# define SPACE 32
# define DOOR 68
# define ENEMY 88

# ifndef REQUIRE_SPACE
#  define REQUIRE_SPACE false
# endif

# ifndef BONUS
#  define BONUS false
# endif

typedef enum e_door_state
{
	IDLE,
	OPENING,
	CLOSING
}				t_door_state;

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_door
{
	t_coord	coord;
	int		state;
	int		pos;
	long	last_move;
}				t_door;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		nr_of_doors;
	t_door	*doors;
}				t_map;

typedef struct s_player
{
	t_coord	pos;
	double	dir;
}				t_player;

typedef struct s_key_state
{
	bool	mv_up;
	bool	mv_dn;
	bool	mv_r;
	bool	mv_l;
	bool	rot_r;
	bool	rot_l;
}				t_key_state;

typedef struct s_image
{
	void	*img_ptr;
	char	*buff;
	int		lsize;
	int		bpp;
	int		endian;
}				t_image;

typedef struct s_textures
{
	t_image	north;
	t_image	east;
	t_image	south;
	t_image	west;
	t_image	floor;
	t_image	ceiling;
	t_image	door;
}				t_textures;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	t_textures	*textures;
	t_door		*active_door;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*imgbuff;
	int			lsize;
	int			bpp;
	int			endian;
	int			floor[3];
	int			ceiling[3];
	double		focal_len;
	long		last_render;
	int			mouse_x;
	t_key_state	key_state;
	double		sin_table[3600];
	double		cos_table[3600];
}				t_data;

typedef struct s_config
{
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	char	*floor;
	char	*ceiling;
	char	*door;
	int		map_start;
}				t_config;

typedef struct s_ray
{
	t_coord	coll;
	bool	is_horiz;
	bool	is_door;
	int		map_item;
	double	dist;
	double	dir;
}				t_ray;

// typedef struct s_vars
// {
// 	void	*mlx;
// 	void	*win;
// 	int		screenwidth;
// 	int		screenheight;
// }				t_vars;

// raycasting
t_ray *cast_rays(t_map *map, t_player p);
void			draw_walls(t_ray *rays, t_data *data);

// Read map
int				read_map(t_data *data, char *fname);
int				read_map_content(t_map *map, int fd, int map_start);
int				get_map_dimensions(t_map *map, int fd);
int				read_to_eoln(int fd, char *value);
int				try_save(char **dest, char *src);
int				save_rgbs(char *str, int dest[3]);
int				find_player(t_map *map, t_player *player);
int				is_valid_map(t_map *map, t_player *player);

// Render
int				load_textures(t_data *data, t_config *config);
void			unload_textures(void *mlx_ptr, t_textures *textures);
void			set_pixel(t_data *data, int c[3], int x, int y);
void			put_pixel_from_img(t_data *data, t_image *src_img,
					t_coord src_coord, t_coord dest_coord);
void			render_frame(t_data *data);
void	draw_minimap(t_data *data, t_ray *rays);
void 			draw_line(t_data *data, t_coord p1, t_coord p2);
//void draw_player(t_data data);

//movement
bool	move_player(t_data *data, bool rev);
bool 	strafe_player(t_data *data, bool left);
bool	rotate_player(t_data *data, bool left, double rotate_speed);

// Doors
bool			move_door(t_data *data, t_door *door);
void			activate_door(t_data *data, t_coord coord);
bool			is_door(t_map *map, t_coord coord);
bool			is_door_visible(t_map *map, t_coord coll, bool is_horiz);

// Events
int				handle_loop(t_data *data);
int				handle_close(t_data *data);
//int				handle_input(int keycode, t_data *data);
int				handle_mouse(void *data);
int				handle_mouse_move(int x, int y, t_data *data);

int handle_key_press(int keycode, t_data *data);
int handle_key_release(int keycode, t_data *data);

// Clean up
void			cleanup(t_data *data);
void			free_map(char **map);
void			free_config(t_config *config);

// Inits
void			init_data(t_data *data);
void			init_textures(t_textures *textures);
void			init_config(t_config *config);
void			init_trig_tables(double *sin_table, double *cos_table);
int				init_window(t_data *data);
void			init_map(t_map *map);
int				init_doors(t_map *map);
void			init_events(t_data *data);

// Utils
char			*file_ext(char *fname);
double			get_angle(char dir);
bool			ft_isnum(char *str);
long			currtime(void);
bool			is_wall(t_coord pos, t_map *map);
char			*ft_strdup2(char *s, size_t n);
int				get_map_item(t_coord pos, t_map *map);
int				get_dir(double angle);
bool			coord_equals(t_coord c, t_coord d);
t_coord			coord_add(t_coord c, t_coord d);
t_coord			pixel2grid(t_coord pixel_pos);
t_coord			get_gridpos_in_front(t_player *player);

// render utils
double norm_angle(double angle);
double	deg_to_rad(double degrees);
int angle_to_index(double angle);

#endif
