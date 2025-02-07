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
	add_key(&fdf->isometric.controls, I_UP, 'w', CTRLI_UP);
	add_key(&fdf->isometric.controls, I_DOWN, 's', CTRLI_DOWN);
	add_key(&fdf->isometric.controls, I_LEFT, 'a', CTRLI_LEFT);
	add_key(&fdf->isometric.controls, I_RIGHT, 'd', CTRLI_RIGHT);
	add_key(&fdf->isometric.controls, I_RX1, 'u', CTRLI_RX1);
	add_key(&fdf->isometric.controls, I_RX2, 'j', CTRLI_RX2);
	add_key(&fdf->isometric.controls, I_RY1, 'i', CTRLI_RY1);
	add_key(&fdf->isometric.controls, I_RY2, 'k', CTRLI_RY2);
	add_key(&fdf->isometric.controls, I_RZ1, 'o', CTRLI_RZ1);
	add_key(&fdf->isometric.controls, I_RZ2, 'l', CTRLI_RZ2);
	add_key(&fdf->isometric.controls, I_ZOOM, '=', CTRLI_ZOOM);
	add_key(&fdf->isometric.controls, I_UNZOOM, '-', CTRLI_UNZOOM);
	add_key(&fdf->isometric.controls, I_YA1, '0', CTRLI_YA1);
	add_key(&fdf->isometric.controls, I_YA2, '9', CTRLI_YA2);
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
