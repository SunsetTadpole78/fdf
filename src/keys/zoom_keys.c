/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:16:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 12:02:21 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	isometric_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->isometric.controls;
	res = 0;
	if (is_key(controls, I_ZOOM, keycode))
	{
		if (fdf->isometric.zoom * fdf->isometric.zoom_base < WIDTH)
		{
			fdf->isometric.zoom *= 1.05;
			res = 1;
		}
	}
	if (is_key(controls, I_UNZOOM, keycode))
	{
		if (fdf->isometric.zoom * fdf->isometric.zoom_base > 0.3)
		{
			fdf->isometric.zoom *= 0.95;
			res = 1;
		}
	}
	return (res);
}

static int	parallel_view(int keycode, t_fdf *fdf)
{
	t_c	controls;
	int	res;

	controls = fdf->parallel.controls;
	res = 0;
	if (is_key(controls, P_ZOOM, keycode))
	{
		if (fdf->parallel.zoom * fdf->parallel.zoom_base < WIDTH)
		{
			fdf->parallel.zoom *= 1.05;
			res = 1;
		}
	}
	if (is_key(controls, P_UNZOOM, keycode))
	{
		if (fdf->parallel.zoom * fdf->parallel.zoom_base > 0.3)
		{
			fdf->parallel.zoom *= 0.95;
			res = 1;
		}
	}
	return (res);
}

int	zoom_check(int keycode, t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		return (isometric_view(keycode, fdf));
	if (fdf->type == PARALLEL)
		return (parallel_view(keycode, fdf));
	return (0);
}
