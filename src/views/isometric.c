/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:16:21 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 11:45:30 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate(t_fdf *fdf, t_vector3 *v3)
{
	float	alpha;
	float	theta;
	float	gamma;
	t_vector3	cpy;
	
	alpha = fdf->display_data->rotate.x * (M_PI / 180);
	theta = fdf->display_data->rotate.y * (M_PI / 180);
	gamma = fdf->display_data->rotate.z * (M_PI / 180);
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
	t_vector2	v2;
	float		zoom;
	t_pixel_data	data;

	zoom = fdf->display_data->zoom * fdf->display_data->zoom_v;
	if (mirror)
		v3.y *= -1;
	v3.x -= fdf->display_data->pivot_point.x;
	v3.y -= fdf->display_data->pivot_point.y;
	v3.z -= fdf->display_data->pivot_point.z;
	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;
	v3.x += 0.5 * zoom;
	v3.z += 0.5 * zoom;
	rotate(fdf, &v3);
		v2.x = WIDTH / 2 + (v3.x - v3.z) * cos(30 * (M_PI / 180));
	v2.y = 2 + HEIGHT / 2 + (v3.x + v3.z) * sin(30 * (M_PI / 180)) - v3.y;
	v2.x += fdf->display_data->offset.x * 60;
	v2.y += fdf->display_data->offset.y * 60;
	data.pos = v2;
	data.depth = v3.z;
	return (data);
}
