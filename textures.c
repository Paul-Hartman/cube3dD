/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:21:55 by wpepping          #+#    #+#             */
/*   Updated: 2024/10/16 18:09:16 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_image(void *mlx_ptr, t_image *img, char *fname)
{
	int	dummy;

	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr,
			fname, &dummy, &dummy);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->lsize, &img->endian);
	return (0);
}

void	init_textures(t_textures *textures)
{
	int i;
	i = 0;
	textures->north.img_ptr = NULL;
	textures->east.img_ptr = NULL;
	textures->south.img_ptr = NULL;
	textures->west.img_ptr = NULL;
	textures->floor.img_ptr = NULL;
	textures->ceiling.img_ptr = NULL;
	while (i < 11)
		textures->enemy[i++].img_ptr = NULL;
}

void load_enemy_texture(t_data *data)
{
	int i;
	i= 0;
	char *filename;
	while(i < 11)
	{
		filename = ft_strjoin("textures/sprite_", ft_itoa(i));
		filename = ft_strjoin(filename, ".xpm");
		if (load_image(data->mlx_ptr, &data->textures->enemy[i],
			filename) == -1)
			break;
		free(filename);
		i++;
	}
}


int	load_textures(t_data *data, t_config *cfg)
{
	bool	xpm;

	if (
		load_image(data->mlx_ptr, &data->textures->north, cfg->north) == -1
		|| load_image(data->mlx_ptr, &data->textures->east, cfg->east) == -1
		|| load_image(data->mlx_ptr, &data->textures->south, cfg->south) == -1
		|| load_image(data->mlx_ptr, &data->textures->west, cfg->west) == -1
		)
		
		return (-1);
	xpm = BONUS && !strncmp(file_ext(cfg->floor), ".xpm", 4);
	if (xpm
		&& load_image(data->mlx_ptr, &data->textures->floor, cfg->floor) == -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->floor, data->floor) == -1)
		return (-1);
	xpm = !strncmp(file_ext(cfg->ceiling), ".xpm", 4);
	if (xpm
		&& load_image(data->mlx_ptr, &data->textures->ceiling,
			cfg->ceiling) == -1)
		return (-1);
	else if (!xpm && save_rgbs(cfg->ceiling, data->ceiling) == -1)
		return (-1);
	load_enemy_texture(data);
	return (0);
}

void unload_enemy_textures(void *mlx_ptr, t_textures *textures)
{
	int i;
	i = 0;
	while (i < 11)
	{
		if (textures->enemy[i].img_ptr)
			mlx_destroy_image(mlx_ptr, textures->enemy[i].img_ptr);
		i++;
	}
}


void	unload_textures(void *mlx_ptr, t_textures *textures)
{
	if (textures->north.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->north.img_ptr);
	if (textures->east.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->east.img_ptr);
	if (textures->south.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->south.img_ptr);
	if (textures->west.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->west.img_ptr);
	if (textures->floor.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->floor.img_ptr);
	if (textures->ceiling.img_ptr)
		mlx_destroy_image(mlx_ptr, textures->ceiling.img_ptr);
	unload_enemy_textures(mlx_ptr, textures);
}
