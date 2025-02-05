/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:32:18 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 12:04:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_controls(t_fdf *fdf)
{
	init_contr(&fdf->parallel.controls);
	add_key(&fdf->parallel.controls, P_UP, 'w', CTRL_UP);
	add_key(&fdf->parallel.controls, P_DOWN, 's', CTRL_DOWN);
	add_key(&fdf->parallel.controls, P_LEFT, 'a', CTRL_LEFT);
	add_key(&fdf->parallel.controls, P_RIGHT, 'd', CTRL_RIGHT);
	add_key(&fdf->parallel.controls, P_RX1, 'u', CTRL_RX1);
	add_key(&fdf->parallel.controls, P_RX2, 'j', CTRL_RX2);
	add_key(&fdf->parallel.controls, P_RY1, 'i', CTRL_RY1);
	add_key(&fdf->parallel.controls, P_RY2, 'k', CTRL_RY2);
	add_key(&fdf->parallel.controls, P_ZOOM, '=', CTRL_ZOOM);
	add_key(&fdf->parallel.controls, P_UNZOOM, '-', CTRL_UNZOOM);
}

void	init_parallel(t_fdf *fdf)
{
	int	t;

	fdf->parallel.rotation.x = 1;
	fdf->parallel.rotation.y = 0;
	fdf->parallel.zoom = 1;
	t = fdf->map->size.x + fdf->map->size.z;
	fdf->parallel.zoom_base = (float)HEIGHT / (fdf->map->size.y + t * sin(30 * (M_PI / 180)));
	if ((float)WIDTH / t < fdf->parallel.zoom_base)
		fdf->parallel.zoom_base = (float)WIDTH / t;
	init_controls(fdf);
}
