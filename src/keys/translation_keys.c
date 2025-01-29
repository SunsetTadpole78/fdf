/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:14:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/29 15:09:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	translation_check(int keycode, t_fdf *fdf)
{
	//printf("%f %f %f\n", fdf->camera.x, fdf->camera.y, fdf->camera.z);
	//printf("%f %f %f\n", fdf->view.yaw, fdf->view.pitch, fdf->view.roll);
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
		fdf->camera.z += 1;
		return (1);
	}
	if (keycode == XK_Down)
	{
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
