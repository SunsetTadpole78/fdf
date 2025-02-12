/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 12:14:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "fdf.h"

int	is_parallel(void)
{
	return (get_fdf()->type == PARALLEL);
}

void	adjust_x(t_fdf *fdf, t_vector3 *v3)
{
	float			temp;

	if ((int)fdf->parallel.rotation.x % 4 == 1)
	{
		temp = v3->y;
		v3->y = v3->z;
		v3->z = -temp;
	}
	else if ((int)fdf->parallel.rotation.x % 4 == 2)
	{
		v3->y = -v3->y;
		v3->z = -v3->z;
	}
	else if ((int)fdf->parallel.rotation.x % 4 == 3)
	{
		temp = v3->y;
		v3->y = -v3->z;
		v3->z = temp;
	}
}

void	adjust_y(t_fdf *fdf, t_vector3 *v3)
{
	float			temp;

	if ((int)fdf->parallel.rotation.y % 4 == 1)
	{
		temp = v3->x;
		v3->x = v3->y;
		v3->y = -temp;
	}
	else if ((int)fdf->parallel.rotation.y % 4 == 2)
	{
		v3->x = -v3->x;
		v3->y = -v3->y;
	}
	else if ((int)fdf->parallel.rotation.y % 4 == 3)
	{
		temp = v3->x;
		v3->x = -v3->y;
		v3->y = temp;
	}
}

static void	adjust_point(t_fdf *fdf, t_vector3 *v3, int mirror, float zoom)
{
	if (mirror)
		v3->y *= -1;
	v3->x -= fdf->pivot_point.x;
	v3->y -= fdf->pivot_point.y;
	v3->z -= fdf->pivot_point.z;
	v3->y *= fdf->parallel.y_amplifier;
	adjust_x(fdf, v3);
	adjust_y(fdf, v3);
	v3->x += fdf->pivot_point.x;
	v3->y += fdf->pivot_point.y;
	v3->z += fdf->pivot_point.z;
	v3->x *= zoom;
	v3->y *= zoom;
	v3->z *= zoom;
}

t_pixel_data	parallel_data(t_fdf *fdf, t_vector3 v3, int mirror)
{
	t_pixel_data	data;
	float			zoom;

	zoom = fdf->parallel.zoom * fdf->parallel.zoom_base;
	adjust_point(fdf, &v3, mirror, zoom);
	data.pos.x = width() / 2.0f + v3.x
		- ((fdf->map->size.x - 1.0f) / 2.0f) * zoom
		+ fdf->parallel.offset.x * zoom;
	data.pos.y = height() / 2.0f + v3.y
		- ((fdf->map->size.y - 1.0f) / 2.0f) * zoom
		+ fdf->parallel.offset.y * zoom;
	data.depth = -v3.z;
	return (data);
}
