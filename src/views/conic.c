/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 09:29:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_conic(void)
{
	return (get_fdf()->type == CONIC);
}

static void	rotate(t_fdf *fdf, t_vector3 *v3)
{
	float	alpha;
	float	theta;
	float	gamma;
	t_vector3	cpy;

	alpha = fdf->conic.rotation.y * (M_PI / 180);
	theta = fdf->conic.rotation.x * (M_PI / 180);
	gamma = fdf->conic.rotation.z * (M_PI / 180);
	cpy = *v3;
	v3->x = cpy.x * cos(theta) * cos(gamma) 
		+ cpy.y * (cos(gamma) * sin(theta) * sin(alpha) - sin(gamma) * cos(alpha)) 
		+ cpy.z * (cos(gamma) * sin(theta) * cos(alpha) + sin(gamma) * sin(alpha));
	v3->y = cpy.x * cos(theta) * sin(gamma) 
		+ cpy.y * (sin(gamma) * sin(theta) * sin(alpha) + cos(gamma) * cos(alpha)) 
		+ cpy.z * (sin(gamma) * sin(theta) * cos(alpha) - cos(gamma) * sin(alpha));
	v3->z = -cpy.x * sin(theta) 
		+ cpy.y * cos(theta) * sin(alpha) 
		+ cpy.z * cos(theta) * cos(alpha);
}

t_pixel_data	cpp(t_fdf *fdf, t_vector3 v3, int  mirror)
{
	float	fovr = fdf->conic.fov * (M_PI / 180);
	float	d = WIDTH / (2 * tan(fovr / 2));
	t_vector2	v;
	float	dist;
	t_pixel_data	data;

	if (mirror)
		v3.y *= -1;
	v3.x -= fdf->pivot_point.x;
	v3.y -= fdf->pivot_point.y;
	v3.z -= fdf->pivot_point.z;
	v3.y *= fdf->conic.y_amplifier;
	rotate(fdf, &v3);
	if (v3.z < fdf->conic.camera.z)
		v3.z = fdf->conic.camera.z + 0.01;
	if (fdf->conic.camera.z == v3.z)
    	v3.z += 0.01;
	dist = sqrt(pow(v3.z - fdf->conic.camera.z, 2));
	if (dist <= 0.01)
    	dist = 0.01;
	v.x = WIDTH / 2 + ((d * (fdf->conic.camera.x - v3.x)) / (fdf->conic.camera.z - v3.z)) / dist;
	v.y = HEIGHT / 2 + ((d * (fdf->conic.camera.y - v3.y)) / (fdf->conic.camera.z - v3.z)) / dist;
	data.pos = v;
	data.depth = -dist;
	return (data);
}
