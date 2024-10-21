#include "cub3d.h"

static t_sprite_info	*set_sprite_info(t_data *data, t_list *info_lst,
							t_sprite *sprite);
static bool				hit_sprite(t_ray *r, t_data *data, double scale,
							t_sprite *sprite);
static int	calculate_sprite_parameters(t_data *data, t_sprite *sprite,
	double *scale, int *screen_y);


void	put_sprite(t_data *data, t_sprite *sprite)
{
	int		i;
	int		j;
	double	scale;
	int		screen_y;
	int		offset;

	offset = calculate_sprite_parameters(data, sprite, &scale, &screen_y);
	i = -1;
	while (++i < (int)(sprite->width * scale) && i < sprite->info->len)
	{
		j = -1;
		while (++j < (int)(sprite->height * scale) && j < WINDOW_HEIGHT
			- screen_y)
		{
			if ((int)(i / scale) >= 0 && i / scale < sprite->width && (int)(j
					/ scale) >= 0 && (int)(j / scale) < sprite->height)
				put_pixel_from_img(data, &data->textures->enemy[sprite->frame],
					(t_coord){(int)((i + offset) / scale), (int)(j / scale)},
					(t_coord){sprite->info->min_x + i, screen_y + j});
		}
	}
}

t_sprite	*get_sprite_coll(t_data *data, t_ray *rays, t_sprite *sprite)
{
	int				i;
	double			dist;
	double			scale;
	t_sprite_info	*sprite_info;
	t_list			*info_lst;

	i = -1;
	dist = get_dist(get_dir_to(data->player->pos, sprite->pos), sprite->pos,
			*data->player);
	scale = data->focal_len / dist;
	info_lst = NULL;
	while (++i < WINDOW_WIDTH)
	{
		if (hit_sprite(&rays[i], data, scale, sprite) && rays[i].dist > dist)
		{
			sprite_info = malloc(sizeof(t_sprite_info));
			sprite_info->dir = rays[i].dir;
			sprite_info->screen_x = i;
			ft_lstadd_back(&info_lst, ft_lstnew(sprite_info));
		}
	}
	if (info_lst)
	{
		sprite_info = set_sprite_info(data, info_lst, sprite);
		ft_lstclear(&info_lst, free);
		sprite->info = sprite_info;
		return (sprite);
	}
	return (NULL);
}

static t_sprite_info	*set_sprite_info(t_data *data, t_list *info_lst,
		t_sprite *sprite)
{
	int				i;
	double			middle;
	int				closest;
	double			dir_to_sprite;
	t_sprite_info	*info;

	i = 0;
	middle = 100;
	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	info = (t_sprite_info *)malloc(sizeof(t_sprite_info));
	info->min_x = ((t_sprite_info *)info_lst->content)->screen_x;
	info->len = ft_lstsize(info_lst);
	while (info_lst)
	{
		if (fabs(((t_sprite_info *)info_lst->content)->dir
				- dir_to_sprite) < middle)
		{
			middle = fabs(((t_sprite_info *)info_lst->content)->dir
					- dir_to_sprite);
			closest = i;
		}
		i++;
		info_lst = info_lst->next;
	}
	info->dir = dir_to_sprite;
	info->middle = closest;
	info->max_x = info->min_x + info->len;
	return (info);
}


static bool	hit_sprite(t_ray *r, t_data *data, double scale, t_sprite *sprite)
{
	int		scaled_width;
	double	dir_to_sprite;
	double	left_angle;
	double	right_angle;
	double	screen_width;

	scaled_width = (int)(sprite->width * scale);
	screen_width = scaled_width * FOV / WINDOW_WIDTH;
	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	left_angle = norm_angle(dir_to_sprite - (screen_width / 2.0));
	right_angle = norm_angle(dir_to_sprite + (screen_width / 2.0));
	if ((r->dir >= left_angle && r->dir <= right_angle)
		|| (left_angle > right_angle && (r->dir >= left_angle
				|| r->dir <= right_angle)))
		return (true);
	return (false);
}


static int	calculate_sprite_parameters(t_data *data, t_sprite *sprite,
		double *scale, int *screen_y)
{
	double	dist;
	double	dir_to_sprite;
	int		width;
	int		offset;

	dir_to_sprite = get_dir_to(data->player->pos, sprite->pos);
	dist = get_dist(dir_to_sprite, sprite->pos, *data->player);
	*scale = data->focal_len / dist;
	width = (int)(sprite->width * (*scale));
	*screen_y = WINDOW_HEIGHT / 2 - (int)(sprite->pos.y / dist);
	offset = 0;
	if (sprite->info->middle <= sprite->info->len / 2
		&& sprite->info->len < width)
		offset = width - sprite->info->len;
	return (offset);
}

