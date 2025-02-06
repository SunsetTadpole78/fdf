/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:14:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 17:45:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	isometric_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->isometric.controls;
	res = 0;
	if (is_key(controls, I_UP, keycode))
	{
		fdf->isometric.offset.y -= 0.5;
		res = 1;
	}
	if (is_key(controls, I_DOWN, keycode))
	{
		fdf->isometric.offset.y += 0.5;
		res = 1;
	}
	if (is_key(controls, I_LEFT, keycode))
	{
		fdf->isometric.offset.x -= 0.5;
		res = 1;
	}
	if (is_key(controls, I_RIGHT, keycode))
	{
		fdf->isometric.offset.x += 0.5;
		res = 1;
	}
	return (res);
}

static int	conic_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->conic.controls;
	res = 0;
	if (is_key(controls, C_FRONT, keycode))
	{
		if (fdf->conic.camera.z < -2)
		{
			fdf->conic.camera.z += 1;
			res = 1;
		}
	}
	else if (is_key(controls, C_BEHIND, keycode))
	{
		t_vector3	p1;
		t_vector3	p2;

		p1.x = 0;
		p1.y = fdf->map->points[(int)fdf->map->size.z - 1][0].pos.y;
		p1.z = (int)fdf->map->size.z - 1;
		p2.x = fdf->map->size.x - 1;
		p2.y = fdf->map->points[(int)fdf->map->size.z - 1][(int)fdf->map->size.x - 1].pos.y;
		p2.z = (int)fdf->map->size.z - 1;
		if (!(fdf->conic.camera.z < fdf->conic.default_z && ft_distance(pixel_pos(fdf, p1, 0).pos, pixel_pos(fdf, p2, 0).pos) <= 50))
		{
			fdf->conic.camera.z -= 1;
			res = 1;
		}
	}
	else if (is_key(controls, C_LEFT, keycode))
	{
		fdf->conic.camera.x -= 1;
		res = 1;
	}
	else if (is_key(controls, C_RIGHT, keycode))
	{
		fdf->conic.camera.x += 1;
		res = 1;
	}
	else if (is_key(controls, C_UP, keycode))
	{
		fdf->conic.camera.y += 1;
		res = 1;
	}
	else if (is_key(controls, C_DOWN, keycode))
	{
		fdf->conic.camera.y -= 1;
		res = 1;
	}
	return (res);
}

static int	parallel_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->parallel.controls;
	res = 0;
	if (is_key(controls, P_UP, keycode))
	{
		fdf->parallel.offset.y -= 1;
		res = 1;
	}
	if (is_key(controls, P_DOWN, keycode))
	{
		fdf->parallel.offset.y += 1;
		res = 1;
	}
	if (is_key(controls, P_LEFT, keycode))
	{
		fdf->parallel.offset.x -= 1;
		res = 1;
	}
	if (is_key(controls, P_RIGHT, keycode))
	{
		fdf->parallel.offset.x += 1;
		res = 1;
	}
	return (res);
}

int	translation_check(int keycode, t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		return (isometric_view(keycode, fdf));
	if (fdf->type == CONIC)
		return (conic_view(keycode, fdf));
	if (fdf->type == PARALLEL)
		return (parallel_view(keycode, fdf));
	return (0);
/*	if (keycode == XK_Left)
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
		
	return (0); */
	/*t_controls	controls;

	controls = fdf->isometric.controls;
	if (keycode == controls.left.v || keycode == controls.right.v)
	{
		fdf->isometric.offset.x += 0.5 * (1 - 2 * (keycode == controls.left.v));
		return (1);
	}
	if (keycode == controls.up.v || keycode == controls.down.v)
	{
		fdf->isometric.offset.y += 0.5 * (1 - 2 * (keycode == controls.up.v));
		return (1);
	}*/
	return (0);
}
