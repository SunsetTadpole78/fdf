/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:00:05 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/06 16:27:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	white(void)
{
	return (0xFFFFFF);
}

int	subject(t_vector3 v, t_vector2 mimay)
{
	float norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return (color_between(0xFFFFFF, 0xFF91FF, norm_y, 1.0f));
}

int	blue(t_vector3 v, t_vector2 mimay)
{
	float norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return color_between(0x2C63DC, 0x00FFFF, norm_y, 1.0f);
}

int	relief(t_vector3 v)
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
	return (from_rgb(rgb));
}

int	pays(t_vector3 v)
{
	if (v.y < -10)
		return (0x142F66);
	if (v.y < -5)
		return (0x214BA5);
	if (v.y < 0)
		return (0x2C63DC);
	if (v.y == 0)
		return (0xFFD800);
	if (v.y < 3)
		return (0x00AF11);
	if (v.y < 5)
		return (0x007F0E);
	if (v.y <= 8)
		return (0x808080);
	return (0xFFFFFF);
}

int	mars(t_vector3 v)
{
	if (v.y < 1 && (((int)v.x) % 3 != 0 || ((int)v.z) % 2 != 0))
		return (0x925E48);
	if(((int)v.x) % 2 != 0 || ((int)v.z) % 5 != 0)
		return (0xB27A5E);
	if (v.y < 1)
		return (0x776B6D);
	if (((int)v.x) % 2 == 0 && ((int)v.z) % 3 != 0)
		return (0xB27A5E);
	if (((int)v.x) % 3 == 0 && ((int)v.z) % 4 != 0)
		return (0xB5683F);
	return (0xB7927E);

}

int	black_and_white(t_vector3 v)
{
	if (v.y == 0)
		return (0);
	return (0xFFFFFF);
}

int	blue_and_yellow(t_vector3 v, t_vector2 mimay)
{
	float norm_y;

	if (mimay.y - mimay.x != 0)
		norm_y = (v.y - mimay.x) / (mimay.y - mimay.x);
	else
		norm_y = 0;
	return color_between(0x00FFFF, 0xC0FF54, norm_y, 1.0f);
}

int	random_c(t_vector3 v)
{
    unsigned int r, g, b;
    float factor;

    factor = sin(v.y * 0.15) * 0.5 + 0.5;
    r = 100 + ((int)(factor * 155) ^ ((int)v.x * 13 % 255));
    g = 100 + ((int)(factor * 155) ^ ((int)v.y * 17 % 255));
    b = 100 + ((int)(factor * 155) ^ ((int)v.z * 19 % 255));
    return ((r << 16) | (g << 8) | b);
}
