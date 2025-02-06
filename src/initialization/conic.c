/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:42:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 15:06:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_controls(t_fdf *fdf)
{
	init_contr(&fdf->conic.controls);
	add_key(&fdf->conic.controls, C_FRONT, 'w', CTRL_UP);
	add_key(&fdf->conic.controls, C_BEHIND, 's', CTRL_DOWN);
	add_key(&fdf->conic.controls, C_LEFT, 'a', CTRL_LEFT);
	add_key(&fdf->conic.controls, C_RIGHT, 'd', CTRL_RIGHT);
	add_key(&fdf->conic.controls, C_UP, 'r', CTRL_UP);
	add_key(&fdf->conic.controls, C_DOWN, 'f', CTRL_DOWN);
	add_key(&fdf->conic.controls, C_RX1, 'u', CTRL_RX1);
	add_key(&fdf->conic.controls, C_RX2, 'j', CTRL_RX2);
	add_key(&fdf->conic.controls, C_RY1, 'i', CTRL_RY1);
	add_key(&fdf->conic.controls, C_RY2, 'k', CTRL_RY2);
	add_key(&fdf->conic.controls, C_RZ1, 'o', CTRL_RZ1);
	add_key(&fdf->conic.controls, C_RZ2, 'l', CTRL_RZ2);
	add_key(&fdf->conic.controls, C_FOV1, '-', CTRL_FOV1);
	add_key(&fdf->conic.controls, C_FOV2, '=', CTRL_FOV2);
}

static void	init_default_z(t_fdf *fdf)
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	t_map	*map;

	map = fdf->map;
	p1.x = (int)(map->size.x / 2);
	p1.y = map->points[(int)map->size.z - 1][(int)((map->size.x - 1) / 2)].pos.y;
	p1.z = map->size.z - 1;
	p2.x = 0;
	p2.y = map->points[(int)(map->size.z - 1)][0].pos.y;
	p2.z = map->size.z - 1;
	p3.x = map->size.x - 1;
	p3.y = map->points[(int)map->size.z - 1][(int)map->size.x - 1].pos.y;
	p3.z = map->size.z - 1;
	fdf->conic.camera.z = 0;
	while ((outside_p(cpp(fdf, p1, 0).pos) || outside_p(cpp(fdf, p2, 0).pos) || outside_p(cpp(fdf, p3, 0).pos)) && fdf->conic.camera.z > -map->size.z * 2)
		fdf->conic.camera.z--;
	fdf->conic.camera.z--;
	fdf->conic.default_z = fdf->conic.camera.z;
}

void	init_conic(t_fdf *fdf)
{
	fdf->conic.camera.x = 0;
	fdf->conic.camera.y = 0;
	fdf->conic.rotation.x = 0;
	fdf->conic.rotation.y = -116;
	fdf->conic.rotation.z = 0;
	fdf->conic.fov = 60;
	fdf->conic.yaw = 0;
	fdf->conic.pitch = 0;
	init_default_z(fdf);
	init_controls(fdf);
}
