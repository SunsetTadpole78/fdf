/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/06 14:22:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	isometric_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->isometric.controls;
	res = 0;
	if (is_key(controls, I_REDUCE_X, keycode))
	{
		fdf->isometric.rotation.x -= 1;
		res = 1;
	}
	if (is_key(controls, I_ADD_X, keycode))
	{
		fdf->isometric.rotation.x += 1;
		res = 1;
	}
	if (is_key(controls, I_REDUCE_Y, keycode))
	{
		fdf->isometric.rotation.y -= 1;
		res = 1;
	}
	if (is_key(controls, I_ADD_Y, keycode))
	{
		fdf->isometric.rotation.y += 1;
		res = 1;
	}
	if (is_key(controls, I_REDUCE_Z, keycode))
	{
		fdf->isometric.rotation.z -= 1;
		res = 1;
	}
	if (is_key(controls, I_ADD_Z, keycode))
	{
		fdf->isometric.rotation.z += 1;
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
	if (is_key(controls, C_RX1, keycode))
	{
		fdf->conic.rotation.x -= 1;
		res = 1;
	}
	if (is_key(controls, C_RX2, keycode))
	{
		fdf->conic.rotation.x += 1;
		res = 1;
	}
	if (is_key(controls, C_RY1, keycode))
	{
		fdf->conic.rotation.y -= 1;
		res = 1;
	}
	if (is_key(controls, C_RY2, keycode))
	{
		fdf->conic.rotation.y += 1;
		res = 1;
	}
	if (is_key(controls, C_RZ1, keycode))
	{
		fdf->conic.rotation.z -= 1;
		res = 1;
	}
	if (is_key(controls, C_RZ2, keycode))
	{
		fdf->conic.rotation.z += 1;
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
	if (is_key(controls, P_RX1, keycode))
	{
		fdf->parallel.rotation.x = ((int)fdf->parallel.rotation.x + 1) % 4;
		res = 1;
	}
	if (is_key(controls, P_RX2, keycode))
	{
		fdf->parallel.rotation.x = ((int)fdf->parallel.rotation.x - 1 + 4) % 4;
		res = 1;
	}
	if (is_key(controls, P_RY1, keycode))
	{
		fdf->parallel.rotation.y = ((int)fdf->parallel.rotation.y + 1) % 4;
		res = 1;
	}
	if (is_key(controls, P_RY2, keycode))
	{
		fdf->parallel.rotation.y = ((int)fdf->parallel.rotation.y - 1 + 4) % 4;
		res = 1;
	}
	return (res);
}

int	rotatation_check(int keycode, t_fdf *fdf)
{
	if (keycode == 'z')
	{
		fdf->conic.yaw -= 1;
		return (1);
	}
	if (keycode == 'x')
	{
		fdf->conic.yaw += 1;
		return (1);
	}
	if (keycode == 'c')
	{
		fdf->conic.pitch -= 1;
		return (1);
	}
	if (keycode == 'v')
	{
		fdf->conic.pitch += 1;
		return (1);
	}
	if (fdf->type == ISOMETRIC)
		return (isometric_view(keycode, fdf));
	if (fdf->type == CONIC)
		return (conic_view(keycode, fdf));
	if (fdf->type == PARALLEL)
		return (parallel_view(keycode, fdf));
	return (0);
}
