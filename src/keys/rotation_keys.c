/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 11:56:11 by lroussel         ###   ########.fr       */
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
	if (fdf->type == ISOMETRIC)
		return (isometric_view(keycode, fdf));
	if (fdf->type == PARALLEL)
		return (parallel_view(keycode, fdf));
	return (0);
}
