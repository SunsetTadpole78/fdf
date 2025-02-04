/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 09:47:23 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#include "fdf.h"

t_pixel_data	pixel_pos(t_fdf *fdf, t_vector3 v3, int mirror)
{
	t_vector2		v2;
	t_pixel_data	data;
	float			zoom;
	float			temp;

	(void)mirror;

	zoom = fdf->display_data->zoom * fdf->display_data->zoom_v;

	v3.x -= fdf->display_data->pivot_point.x;
	v3.y -= fdf->display_data->pivot_point.y;
	v3.z -= fdf->display_data->pivot_point.z;
	if ((int)fdf->par.x % 4 == 1)
	{
		temp = v3.y;
		v3.y = v3.z;
		v3.z = -temp;
	}
	else if ((int)fdf->par.x % 4 == 2)
	{
		v3.y = -v3.y;
		v3.z = -v3.z;
	}
	else if ((int)fdf->par.x % 4 == 3)
	{
		temp = v3.y;
		v3.y = -v3.z;
		v3.z = temp;
	}
	if ((int)fdf->par.y % 4 == 1)
	{
		temp = v3.x;
		v3.x = v3.y;
		v3.y = -temp;
	}
	else if ((int)fdf->par.y % 4 == 2)
	{
		v3.x = -v3.x;
		v3.y = -v3.y;
	}
	else if ((int)fdf->par.y % 4 == 3)
	{
		temp = v3.x;
		v3.x = -v3.y;
		v3.y = temp;
	}
	v3.x += fdf->display_data->pivot_point.x;
	v3.y += fdf->display_data->pivot_point.y;
	v3.z += fdf->display_data->pivot_point.z;
	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;

	v2.x = WIDTH / 2 + v3.x - ((fdf->map->size.x - 1) / 2) * zoom;
	v2.y = HEIGHT / 2 + v3.y - ((fdf->map->size.y - 1) / 2) * zoom;

	data.pos = v2;
	data.depth = v3.z;
	return (data);
}
