/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 12:10:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_conic(void)
{
	return (get_fdf()->type == CONIC);
}

static void	rotate(t_fdf *fdf, t_vector3 *v3)
{
	float		alpha;
	float		theta;
	float		gamma;
	t_vector3	cpy;

	alpha = fdf->conic.rotation.y * (M_PI / 180);
	theta = fdf->conic.rotation.x * (M_PI / 180);
	gamma = fdf->conic.rotation.z * (M_PI / 180);
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

static void	adjust_point(t_fdf *fdf, t_vector3 *v3, int mirror)
{
	if (mirror)
		v3->y *= -1.0f;
	v3->y *= fdf->conic.y_amplifier;
	v3->x -= fdf->pivot_point.x;
	v3->y -= fdf->pivot_point.y;
	v3->z -= fdf->pivot_point.z;
	rotate(fdf, v3);
}

t_pixel_data	cpp(t_fdf *fdf, t_vector3 v3, int mirror)
{
	float			fovr;
	float			d;
	float			dist;
	t_pixel_data	data;

	fovr = fdf->conic.fov * (M_PI / 180);
	d = width() / (2.0f * tan(fovr / 2.0f));
	adjust_point(fdf, &v3, mirror);
	if (v3.z < fdf->conic.camera.z)
		v3.z = fdf->conic.camera.z + 0.01f;
	if (fdf->conic.camera.z == v3.z)
		v3.z += 0.01f;
	dist = sqrt(pow(v3.z - fdf->conic.camera.z, 2));
	if (dist <= 0.01f)
		dist = 0.01f;
	data.pos.x = width() / 2.0f + ((d * (fdf->conic.camera.x - v3.x))
			/ (fdf->conic.camera.z - v3.z)) / dist;
	data.pos.y = height() / 2.0f + ((d * (fdf->conic.camera.y - v3.y))
			/ (fdf->conic.camera.z - v3.z)) / dist;
	data.depth = -dist;
	return (data);
}
