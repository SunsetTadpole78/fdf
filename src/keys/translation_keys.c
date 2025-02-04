/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:14:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 09:41:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	translation_check(int keycode, t_fdf *fdf)
{
	//printf("%f %f %f\n", fdf->camera.x, fdf->camera.y, fdf->camera.z);
	printf("%f %f %f\n", fdf->display_data->rotate.x, fdf->display_data->rotate.y, fdf->display_data->rotate.z);

	if (keycode == XK_Up)    fdf->par.x = (int)(fdf->par.x + 1) % 4;
if (keycode == XK_Down)  fdf->par.x = (int)(fdf->par.x - 1 + 4) % 4;

if (keycode == XK_Right)  fdf->par.y = (int)(fdf->par.y + 1) % 4;
if (keycode == XK_Left) fdf->par.y = (int)(fdf->par.y - 1 + 4) % 4;
printf("%f %f\n", fdf->par.x, fdf->par.y);

	return (1);
	if (keycode == XK_Left)
	{
		fdf->camera.x -= 1;
		return (1);
	}
	if (keycode == XK_Right)
	{
		fdf->camera.x += 1;
		return (1);
	}
	if (keycode == XK_Up)
	{
		if (fdf->camera.z >= -2)
			return (0);
		fdf->camera.z += 1;
		return (1);
	}
	if (keycode == XK_Down)
	{
		t_vector3	p1;
		t_vector3	p2;

		p1.x = 0;
		p1.y = fdf->map->points[(int)fdf->map->size.z - 1][0].pos.y;
		p1.z = (int)fdf->map->size.z - 1;
		p2.x = fdf->map->size.x - 1;
		p2.y = fdf->map->points[(int)fdf->map->size.z - 1][(int)fdf->map->size.x].pos.y;
		p2.z = (int)fdf->map->size.z - 1;
		if (fdf->camera.z < fdf->camerai && ft_distance(pixel_pos(fdf, p1, 0).pos, pixel_pos(fdf, p2, 0).pos) <= 50)
			return (0);
		fdf->camera.z -= 1;
		return (1);
	}
	if (keycode == 65366)
	{
		fdf->camera.y -= 1;
		return (1);
	}
	if (keycode == 65365)
	{
		fdf->camera.y += 1;
		return (1);
	}
	if (keycode == 'z')
	{
		fdf->view.pitch -= 1;
		return (1);
	}
	if (keycode == 'x')
	{
		fdf->view.pitch += 1;
		return (1);
	}
	if (keycode == 'c')
	{
		fdf->view.yaw -= 1;
		return (1);
	}
	if (keycode == 'v')
	{
		fdf->view.yaw += 1;
		return (1);
	}
	if (keycode == 'b')
	{
		fdf->view.roll -= 1;
		return (1);
	}
	if (keycode == 'n')
	{
		fdf->view.roll += 1;
		return (1);
	}
	if (keycode == '.')
	{
		fdf->view.fov -= 1;
		return (1);
	}
	if (keycode == '/')
	{
		fdf->view.fov += 1;
		return (1);
	}
		
	return (0);
	if (keycode == fdf->controls.left.v || keycode == fdf->controls.right.v)
	{
		fdf->display_data->offset.x += 0.5 * (1 - 2 * (keycode == fdf->controls.left.v));
		return (1);
	}
	if (keycode == fdf->controls.up.v || keycode == fdf->controls.down.v)
	{
		fdf->display_data->offset.y += 0.5 * (1 - 2 * (keycode == fdf->controls.up.v));
		return (1);
	}
	return (0);
}
