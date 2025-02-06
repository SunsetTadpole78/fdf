/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:29:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 16:30:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_controls(t_fdf *fdf)
{
	init_contr(&fdf->isometric.controls);
	add_key(&fdf->isometric.controls, I_UP, 'w', CTRL_UP);
	add_key(&fdf->isometric.controls, I_DOWN, 's', CTRL_DOWN);
	add_key(&fdf->isometric.controls, I_LEFT, 'a', CTRL_LEFT);
	add_key(&fdf->isometric.controls, I_RIGHT, 'd', CTRL_RIGHT);
	add_key(&fdf->isometric.controls, I_REDUCE_X, 'u', CTRL_REDUCE_X);
	add_key(&fdf->isometric.controls, I_ADD_X, 'j', CTRL_ADD_X);
	add_key(&fdf->isometric.controls, I_REDUCE_Y, 'i', CTRL_REDUCE_Y);
	add_key(&fdf->isometric.controls, I_ADD_Y, 'k', CTRL_ADD_Y);
	add_key(&fdf->isometric.controls, I_REDUCE_Z, 'o', CTRL_REDUCE_Z);
	add_key(&fdf->isometric.controls, I_ADD_Z, 'l', CTRL_ADD_Z);
	add_key(&fdf->isometric.controls, I_ZOOM, '=', CTRL_ZOOM);
	add_key(&fdf->isometric.controls, I_UNZOOM, '-', CTRL_UNZOOM);
	add_key(&fdf->isometric.controls, I_YA1, '0', CTRL_YA1);
	add_key(&fdf->isometric.controls, I_YA2, '9', CTRL_YA2);
}

void	init_isometric(t_fdf *fdf)
{
	int	t;

	fdf->isometric.offset.x = 0;
	fdf->isometric.offset.y = 0;
	fdf->isometric.rotation.x = 0;
	fdf->isometric.rotation.y = 0;
	fdf->isometric.rotation.z = 0;
	fdf->isometric.zoom = 1;
	t = fdf->map->size.x + fdf->map->size.z;
	fdf->isometric.zoom_base = (float)HEIGHT / (fdf->map->size.y + t * sin(30 * (M_PI / 180)));
	if ((float)WIDTH / t < fdf->isometric.zoom_base)
		fdf->isometric.zoom_base = (float)WIDTH / t;
	fdf->isometric.axis = 1;
	fdf->isometric.mirror = 0;
	fdf->isometric.y_amplifier = 1;
	init_controls(fdf);
}
