#include "cub3d.h"



void put_sprite(t_data *data, t_enemy enemy, t_image tex)
{
	int i;
	int j;
	double dist;
	double scale;

	
	dist = sqrt(pow(data->player->pos.x - enemy.x, 2) + pow(data->player->pos.y - enemy.y, 2));

	scale = ((enemy.height / dist) * data->focal_len)/ enemy.height;
	i = 0;
	while(i < (int)(enemy.width * scale))
	{
		j = 0;
		while(j < (int)(enemy.height * scale))
		{
			put_pixel_from_img(data, &tex, (t_coord){(int)(i / scale), (int)(j / scale)}, (t_coord){enemy.x + i, enemy.y + j});
			j++;
		}
		i++;
	}
}