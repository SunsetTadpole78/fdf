/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:32:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:32:33 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mars(t_vector3 v)
{
	if (v.y < 1 && (((int)v.x) % 3 != 0 || ((int)v.z) % 2 != 0))
		return (0x925E48);
	if (((int)v.x) % 2 != 0 || ((int)v.z) % 5 != 0)
		return (0xB27A5E);
	if (v.y < 1)
		return (0x776B6D);
	if (((int)v.x) % 2 == 0 && ((int)v.z) % 3 != 0)
		return (0xB27A5E);
	if (((int)v.x) % 3 == 0 && ((int)v.z) % 4 != 0)
		return (0xB5683F);
	return (0xB7927E);
}

int	btow(t_vector3 v)
{
	if (v.y == 0)
		return (0);
	return (0xFFFFFF);
}

int	btoy(t_vector3 v, t_vector2 mimay)
{
	float	norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return (ft_colorbetween(0x00FFFF, 0xC0FF54, norm_y, 1.0f));
}

int	sin_col(t_vector3 v)
{
	t_rgb	rgb;
	float	factor;

	factor = sin(v.y * 0.15) * 0.5 + 0.5;
	rgb.r = 100 + ((int)(factor * 155) ^ ((int)v.x * 13 % 255));
	rgb.g = 100 + ((int)(factor * 155) ^ ((int)v.y * 17 % 255));
	rgb.b = 100 + ((int)(factor * 155) ^ ((int)v.z * 19 % 255));
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
