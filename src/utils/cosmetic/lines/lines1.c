/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:00:05 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 13:36:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	wtop(t_vector3 v, t_vector2 mimay)
{
	float	norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return (ft_colorbetween(0xFFFFFF, 0xFF91FF, norm_y, 1.0f));
}

int	btob(t_vector3 v, t_vector2 mimay)
{
	float	norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return (ft_colorbetween(0x2C63DC, 0x00FFFF, norm_y, 1.0f));
}

int	heat(t_vector3 v)
{
	if (v.y < 0)
		return (0x2C63DC);
	if (v.y == 0)
		return (0xFFD800);
	return (0xD30000);
}

int	rgb(t_vector3 v, t_vector2 mimay, t_vector3 size)
{
	t_rgb		rgb;
	const int	min_value = 50;

	rgb.t = 0;
	rgb.r = min_value + (255 - min_value) * v.x / size.x;
	rgb.g = min_value + (255 - min_value) * ft_abs(v.y) / size.y;
	rgb.b = min_value + (255 - min_value) * v.z / size.z;
	(void)mimay;
	return (ft_fromrgb(rgb));
}

int	ground(t_vector3 v)
{
	if (v.y < -10)
		return (0x142F66);
	if (v.y < -5)
		return (0x214BA5);
	if (v.y <= 0)
		return (0x2C63DC);
	if (v.y < 3)
		return (0x00AF11);
	if (v.y < 5)
		return (0x007F0E);
	if (v.y <= 8)
		return (0x808080);
	return (0xFFFFFF);
}
