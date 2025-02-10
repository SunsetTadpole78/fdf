/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:32:18 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/06 17:04:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_controls(t_fdf *fdf)
{
	init_contr(&fdf->parallel.controls);
	add_key(&fdf->parallel.controls, P_UP, 'w', CTRLP_UP);
	add_key(&fdf->parallel.controls, P_DOWN, 's', CTRLP_DOWN);
	add_key(&fdf->parallel.controls, P_LEFT, 'a', CTRLP_LEFT);
	add_key(&fdf->parallel.controls, P_RIGHT, 'd', CTRLP_RIGHT);
	add_key(&fdf->parallel.controls, P_RX1, 65362, CTRLP_RX1);
	add_key(&fdf->parallel.controls, P_RX2, 65364, CTRLP_RX2);
	add_key(&fdf->parallel.controls, P_RY1, 65361, CTRLP_RY1);
	add_key(&fdf->parallel.controls, P_RY2, 65363, CTRLP_RY2);
	add_key(&fdf->parallel.controls, P_ZOOM, '=', CTRLP_ZOOM);
	add_key(&fdf->parallel.controls, P_UNZOOM, '-', CTRLP_UNZOOM);
	add_key(&fdf->parallel.controls, P_YA1, '0', CTRLP_YA1);
	add_key(&fdf->parallel.controls, P_YA2, '9', CTRLP_YA2);
}

void	init_parallel(t_fdf *fdf)
{
	int	t;

	fdf->parallel.rotation.x = 1;
	fdf->parallel.rotation.y = 0;
	fdf->parallel.offset.x = 0;
	fdf->parallel.offset.y = 0;
	fdf->parallel.zoom = 1;
	t = fdf->map->size.x + fdf->map->size.z;
	fdf->parallel.zoom_base = (float)height() / (fdf->map->size.y + t * sin(30 * (M_PI / 180)));
	if ((float)width() / t < fdf->parallel.zoom_base)
		fdf->parallel.zoom_base = (float)width() / t;
	fdf->parallel.axis = 1;
	fdf->parallel.y_amplifier = 1;
	init_controls(fdf);
}
