/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 15:46:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	chars_to_float(char *nbr)
{
	float			res;
	unsigned int	i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nbr[0] == '-')
	{
		i = 1;
		sign = -1;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_distance(t_vector2 v1, t_vector2 v2)
{
	return (sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2)));
}

void	fix_angle(float *v)
{
	while (*v < 0)
		*v += 360;
	while (*v > 360)
		*v -= 360;
}
