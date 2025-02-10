/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:53:20 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 09:30:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>
#include "fdf.h"

int	is_parallel(void)
{
	return (get_fdf()->type == PARALLEL);
}

t_pixel_data	ppp(t_fdf *fdf, t_vector3 v3, int mirror)
{
	t_vector2		v2;
	t_pixel_data	data;
	float			zoom;
	float			temp;

	if (mirror)
		v3.y *= -1;
	zoom = fdf->parallel.zoom * fdf->parallel.zoom_base;
	v3.x -= fdf->pivot_point.x;
	v3.y -= fdf->pivot_point.y;
	v3.z -= fdf->pivot_point.z;
	v3.y *= fdf->parallel.y_amplifier;
	if ((int)fdf->parallel.rotation.x % 4 == 1)
	{
		temp = v3.y;
		v3.y = v3.z;
		v3.z = -temp;
	}
	else if ((int)fdf->parallel.rotation.x % 4 == 2)
	{
		v3.y = -v3.y;
		v3.z = -v3.z;
	}
	else if ((int)fdf->parallel.rotation.x % 4 == 3)
	{
		temp = v3.y;
		v3.y = -v3.z;
		v3.z = temp;
	}
	if ((int)fdf->parallel.rotation.y % 4 == 1)
	{
		temp = v3.x;
		v3.x = v3.y;
		v3.y = -temp;
	}
	else if ((int)fdf->parallel.rotation.y % 4 == 2)
	{
		v3.x = -v3.x;
		v3.y = -v3.y;
	}
	else if ((int)fdf->parallel.rotation.y % 4 == 3)
	{
		temp = v3.x;
		v3.x = -v3.y;
		v3.y = temp;
	}
	v3.x += fdf->pivot_point.x;
	v3.y += fdf->pivot_point.y;
	v3.z += fdf->pivot_point.z;
	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;

	v2.x = width() / 2 + v3.x - ((fdf->map->size.x - 1) / 2) * zoom;
	v2.y = height() / 2 + v3.y - ((fdf->map->size.y - 1) / 2) * zoom;
	v2.x += fdf->parallel.offset.x * zoom;
	v2.y += fdf->parallel.offset.y * zoom;

	data.pos = v2;
	data.depth = -v3.z;
	return (data);
}
