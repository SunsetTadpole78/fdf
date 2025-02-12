/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:16:21 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:43:18 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_isometric(void)
{
	return (get_fdf()->type == ISOMETRIC);
}

static void	rotate(t_fdf *fdf, t_vector3 *v3)
{
	float		alpha;
	float		theta;
	float		gamma;
	t_vector3	cpy;

	alpha = fdf->isometric.rotation.x * (M_PI / 180.0f);
	theta = fdf->isometric.rotation.y * (M_PI / 180.0f);
	gamma = fdf->isometric.rotation.z * (M_PI / 180.0f);
	cpy = *v3;
	v3->x = cpy.x * cos(theta) * cos(gamma)
		+ cpy.y * (cos(gamma) * sin(theta)
			* sin(alpha) - sin(gamma) * cos(alpha))
		+ cpy.z * (cos(gamma) * sin(theta)
			* cos(alpha) + sin(gamma) * sin(alpha));
	v3->y = cpy.x * cos(theta) * sin(gamma)
		+ cpy.y * (sin(gamma) * sin(theta)
			* sin(alpha) + cos(gamma) * cos(alpha))
		+ cpy.z * (sin(gamma) * sin(theta)
			* cos(alpha) - cos(gamma) * sin(alpha));
	v3->z = -cpy.x * sin(theta)
		+ cpy.y * cos(theta) * sin(alpha)
		+ cpy.z * cos(theta) * cos(alpha);
}

static void	adjust_point(t_fdf *fdf, t_vector3 *v3, int mirror, float zoom)
{
	if (mirror)
		v3->y *= -1.0f;
	v3->x -= fdf->pivot_point.x;
	v3->y -= fdf->pivot_point.y;
	v3->z -= fdf->pivot_point.z;
	v3->y *= fdf->isometric.y_amplifier;
	v3->x *= zoom;
	v3->y *= zoom;
	v3->z *= zoom;
	v3->x += 0.5f * zoom;
	v3->z += 0.5f * zoom;
	rotate(fdf, v3);
}

t_pixel_data	isometric_data(t_fdf *fdf, t_vector3 v3, int mirror)
{
	float			zoom;
	t_pixel_data	data;

	zoom = fdf->isometric.zoom * fdf->isometric.zoom_base;
	adjust_point(fdf, &v3, mirror, zoom);
	data.pos.x = width() / 2.0f + (v3.x - v3.z) * cos(30 * (M_PI / 180))
		+ fdf->isometric.offset.x * (width() / 30);
	data.pos.y = 2.0f + height() / 2.0f + (v3.x + v3.z) * sin(30 * (M_PI / 180))
		- v3.y + fdf->isometric.offset.y * (height() / 30);
	data.depth = v3.z;
	return (data);
}
