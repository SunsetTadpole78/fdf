/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:51:46 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 12:25:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rnb(t_vector2 v, int w, int h)
{
	return (((int)v.x * 255) / w
		+ ((((w - (int)v.x) * 255) / w) << 16)
		+ ((((int)v.y * 255) / h) << 8));
}

int	ver(t_vector2 v, int w, int h)
{
	int	g;

	g = ((int)v.y * 255) / h;
	return ((128 | (g << 8) | ((255 - g) << 16)) + (w - w));
}

int	hor(t_vector2 v, int w, int h)
{
	int	r;

	r = ((int)v.x * 255) / w;
	return ((r | ((255 - r) << 8) | (128 << 16)) + (h - h));
}

int	diag(t_vector2 v, int w, int h)
{
	return ((((int)v.x * 255) / w)
		| ((255 - (((int)v.x + (int)v.y) * 255) / (w + h)) << 8)
		| ((((int)v.y * 255) / h) << 16));
}

int	diag_m(t_vector2 v, int w, int h)
{
	return ((((int)v.x * 255) / w) * 2
		| ((255 - (((int)v.x + (int)v.y) * 255) / (w + h)) * 2 << 8)
		| ((((int)v.y * 255) / h) * 2 << 16));
}

int	circ(t_vector2 v, int w, int h)
{
	float	dx;
	float	dy;
	float	ratio;
	int		intensity;

	dx = v.x - w / 2.0f;
	dy = v.y - h / 2.0f;
	ratio = (sqrt(dx * dx + dy * dy)) / (sqrt((w / 2.0f) * (w / 2.0f)
				+ (h / 2.0f) * (h / 2.0f)));
	intensity = (int)(ratio * 255);
	return ((255 - intensity) | (intensity << 8)
		| (((int)(128 + 127 * sin(ratio * M_PI))) << 16));
}

int	circ_m(t_vector2 v, int w, int h)
{
	float	dx;
	float	dy;
	float	ratio;
	int		intensity;

	dx = v.x - w / 2.0f;
	dy = v.y - h / 2.0f;
	ratio = (sqrt(dx * dx + dy * dy)) / (sqrt((w / 2.0f) * (w / 2.0f)
				+ (h / 2.0f) * (h / 2.0f)));
	intensity = (int)(ratio * 255);
	return (((255 - intensity) * 2)
		| ((intensity * 2) << 8)
		| ((((int)(128 + 127 * sin(ratio * M_PI))) * 2) << 16));
}

int	rnb2(t_vector2 v, int w, int h)
{
	float	ratio;

	ratio = (float)((int)v.x + (int)v.y) / (w + h);
	return (((int)(127 * (1 + sin(ratio * 2 * M_PI))))
			| (((int)(127 * (1 + sin(ratio * 2 * M_PI + 2 * M_PI / 3))))
			<< 8)
			| (((int)(127 * (1 + sin(ratio * 2 * M_PI + 4 * M_PI / 3))))
			<< 16));
}

int	rnb2_m(t_vector2 v, int w, int h)
{
	float	ratio;

	ratio = (float)((int)v.x + (int)v.y) / (w + h);
	return (((int)(127 * (1 + sin(ratio * 2 * M_PI)))) * 2
			| ((((int)(127 * (1 + sin(ratio * 2 * M_PI + 2 * M_PI / 3)))) * 2)
			<< 8)
			| ((((int)(127 * (1 + sin(ratio * 2 * M_PI + 4 * M_PI / 3)))) * 2)
			<< 16));
}

int	spir(t_vector2 v, int w, int h)
{
	float	dx;
	float	dy;
	float	angle;
	int		i;

	dx = v.x - w / 2.0f;
	dy = v.y - h / 2.0f;
	angle = atan2(dy, dx);
	i = (int)((sqrt(dx * dx + dy * dy) / (sqrt(w * w + h * h) / 2)) * 255);
	return (((int)(127 * (1 + sin(angle + i / 255.0f))))
		| (((int)(127 * (1 + cos(angle - i / 255.0f)))) << 8)
		| ((255 - i) << 16));
}

int	spir_m(t_vector2 v, int w, int h)
{
	float	dx;
	float	dy;
	float	angle;
	int		i;

	dx = v.x - w / 2.0f;
	dy = v.y - h / 2.0f;
	angle = atan2(dy, dx);
	i = (int)((sqrt(dx * dx + dy * dy) / (sqrt(w * w + h * h) / 2)) * 255);
	return ((int)(127 * (1 + sin(angle + i / 255.0f)) * 2) |
		((int)(127 * (1 + cos(angle - i / 255.0f)) * 2) << 8) |
		((int)((255 - i) * 2) << 16));
}
