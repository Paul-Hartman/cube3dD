/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:52:36 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/27 18:04:10 by wpepping         ###   ########.fr       */
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

typedef struct s_main {
	char	*imgbuff,
	int		lsize,
	int		bpp,
	int		endian
} t_main

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

void	cleanup(t_data *data);

#endif
