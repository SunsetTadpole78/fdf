/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:52:49 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 15:44:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	moves(t_conic *conic, t_c controls, t_fdf *fdf)
{
	t_point	p1;
	t_point	p2;

	if (is_pressed(controls, C_FRONT) && conic->camera.z < -2)
		conic->camera.z += 0.2f;
	else if (is_pressed(controls, C_BEHIND))
	{
		p1 = fdf->map->points[(int)fdf->map->size.z - 1][0];
		p2 = fdf->map->points[(int)fdf->map->size.z - 1]
		[(int)fdf->map->size.x - 1];
		if (!(conic->camera.z < conic->default_z
				&& ft_distance(pixel_pos(fdf, p1, 0).pos,
					pixel_pos(fdf, p2, 0).pos) <= 50))
			conic->camera.z -= 0.2f;
	}
	else if (is_pressed(controls, C_LEFT))
		conic->camera.x -= 0.2f;
	else if (is_pressed(controls, C_RIGHT))
		conic->camera.x += 0.2f;
	else if (is_pressed(controls, C_UP))
		conic->camera.y += 0.2f;
	else if (is_pressed(controls, C_DOWN))
		conic->camera.y -= 0.2f;
}

static void	rotations(t_conic *conic, t_c controls)
{
	if (is_pressed(controls, C_RX1))
		conic->rotation.x -= 0.6f;
	if (is_pressed(controls, C_RX2))
		conic->rotation.x += 0.6f;
	if (is_pressed(controls, C_RY1))
		conic->rotation.y -= 0.6f;
	if (is_pressed(controls, C_RY2))
		conic->rotation.y += 0.6f;
	if (is_pressed(controls, C_RZ1))
		conic->rotation.z -= 0.6f;
	if (is_pressed(controls, C_RZ2))
		conic->rotation.z += 0.6f;
	fix_angle(&conic->rotation.x);
	fix_angle(&conic->rotation.y);
	fix_angle(&conic->rotation.z);
}

static void	fov(t_conic *conic, t_c controls)
{
	if (is_pressed(controls, C_FOV1) && conic->fov < 179)
		conic->fov += 0.5f;
	if (is_pressed(controls, C_FOV2) && conic->fov > 1)
		conic->fov -= 0.5f;
}

static void	y_amplifier(t_conic *conic, t_c controls)
{
	if (is_pressed(controls, C_YA1))
		conic->y_amplifier += 0.25f;
	if (is_pressed(controls, C_YA2))
		conic->y_amplifier -= 0.25f;
}

void	conic_key_event(t_fdf *fdf)
{
	t_conic	*conic;
	t_c		controls;

	conic = &fdf->conic;
	controls = conic->controls;
	moves(conic, controls, fdf);
	rotations(conic, controls);
	fov(conic, controls);
	y_amplifier(conic, controls);
}
