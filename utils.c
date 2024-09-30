/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpepping <wpepping@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:41:16 by wpepping          #+#    #+#             */
/*   Updated: 2024/09/30 15:13:43 by wpepping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_remove(char *str, char c)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	while (str[i])
		if (str[i++] != c)
			len++;
	result = malloc((len + 1) * sizeof(char));
	while (i >= 0)
	{
		if (str[i] != c)
			result[len--] = str[i];
		i--;
	}
	return (result);
}
