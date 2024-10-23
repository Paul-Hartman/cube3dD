/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:21:55 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/23 15:44:18 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_image(void *mlx_ptr, t_image *img, char *fname)
{
	int	dummy;

	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &dummy, &dummy);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->lsize,
			&img->endian);
	return (0);
}

static int	load_gun_textures(t_data *data)
{
	int		i;
	char	filename[18];

	i = 0;
	ft_strlcpy(filename, GUN_TEXTURE_BASE_NAME, 18);
	while (i < 3)
	{
		if (load_image(data->mlx_ptr, &data->textures->gun[i], filename) == -1)
			return (-1);
		filename[12]++;
		i++;
	}
	return (0);
}

static int	load_enemy_texture(t_data *data)
{
	int		i;
	char	*index;
	char	filename[30];

	i = 0;
	while (i < 11)
	{
		ft_strlcpy(filename, "textures/sprite_", 17);
		index = ft_itoa(i);
		ft_strlcat(filename, index, 30);
		ft_strlcat(filename, ".xpm", 30);
		if (load_image(data->mlx_ptr, &data->textures->enemy[i], filename)
			== -1)
			return (-1);
		free(index);
		i++;
	}
	return (0);
}

static int	load_healthbar_texture(t_data *data)
{
	int		i;
	char	*index;
	char	filename[30];

	i = 0;
	while (i < 9)
	{
		ft_strlcpy(filename, "textures/healthbar_", 20);
		index = ft_itoa(i);
		ft_strlcat(filename, index, 30);
		ft_strlcat(filename, ".xpm", 30);
		if (load_image(data->mlx_ptr, &data->textures->healthbar[i], filename)
			== -1)
			return (-1);
		free(index);
		i++;
	}
	return (0);
}

static int	load_bonus_textures(t_data *data, t_config *cfg)
{
	if (load_image(data->mlx_ptr, &data->textures->door, cfg->door) == -1)
		return (-1);
	if (load_enemy_texture(data) == -1)
		return (-1);
	if (load_gun_textures(data) == -1)
		return (-1);
	if (load_healthbar_texture(data) == -1)
		return (-1);
	return (0);
}

int	load_textures(t_data *data, t_config *cfg)
{
	bool	xpm;

	if (load_image(data->mlx_ptr, &data->textures->north, cfg->north) == -1
		|| load_image(data->mlx_ptr, &data->textures->east, cfg->east) == -1
		|| load_image(data->mlx_ptr, &data->textures->south, cfg->south) == -1
		|| load_image(data->mlx_ptr, &data->textures->west, cfg->west) == -1)
		return (-1);
	xpm = BONUS && !strncmp(file_ext(cfg->floor), ".xpm", 4);
	if (xpm && load_image(data->mlx_ptr, &data->textures->floor, cfg->floor)
		== -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->floor, data->floor) == -1)
		return (-1);
	xpm = !strncmp(file_ext(cfg->ceiling), ".xpm", 4);
	if (xpm && load_image(data->mlx_ptr, &data->textures->ceiling,
			cfg->ceiling) == -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->ceiling, data->ceiling) == -1)
		return (-1);
	if (BONUS && load_bonus_textures(data, cfg) == -1)
		return (-1);
	return (0);
}
