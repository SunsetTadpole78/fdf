/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/30 15:34:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate(t_fdf *fdf, t_vector3 *v3)
{
	float	alpha;
	float	theta;
	float	gamma;
	t_vector3	cpy;

	alpha = fdf->view.pitch * (M_PI / 180);
	theta = fdf->view.yaw * (M_PI / 180);
	gamma = fdf->view.roll * (M_PI / 180);
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

t_pixel_data	pixel_pos(t_fdf *fdf, t_vector3 v3, int  mirror)
{
	float	fovr = fdf->view.fov * (M_PI / 180);
	float	d = WIDTH / (2 * tan(fovr / 2));
	t_vector2	v;
	float	dist;
	t_pixel_data	data;

	v3.x -= fdf->display_data->pivot_point.x;
	v3.y -= fdf->display_data->pivot_point.y;
	v3.z -= fdf->display_data->pivot_point.z;
	if (mirror)
		v3.y *= -1;
	rotate(fdf, &v3);
	if (v3.z < fdf->camera.z)
		v3.z = fdf->camera.z + 0.01;
	if (fdf->camera.z == v3.z)
    	v3.z += 0.01;
	dist = sqrt(pow(v3.z - fdf->camera.z, 2));
	if (dist <= 0.01)
    	dist = 0.01;
	v.x = WIDTH / 2 + ((d * (fdf->camera.x - v3.x)) / (fdf->camera.z - v3.z)) / dist;
	v.y = HEIGHT / 2 + ((d * (fdf->camera.y - v3.y)) / (fdf->camera.z - v3.z)) / dist;
	data.pos = v;
	data.depth = -dist;
	return (data);
}
