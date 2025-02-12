/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:59:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:13:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translations(t_isometric *isometric, t_controls controls)
{
	if (is_pressed(controls, I_UP))
		isometric->offset.y -= 0.1f;
	if (is_pressed(controls, I_DOWN))
		isometric->offset.y += 0.1f;
	if (is_pressed(controls, I_LEFT))
		isometric->offset.x -= 0.1f;
	if (is_pressed(controls, I_RIGHT))
		isometric->offset.x += 0.1f;
}

static void	rotations(t_isometric *isometric, t_controls controls)
{
	if (is_pressed(controls, I_RX1))
		isometric->rotation.x -= 0.6f;
	if (is_pressed(controls, I_RX2))
		isometric->rotation.x += 0.6f;
	if (is_pressed(controls, I_RY1))
		isometric->rotation.y -= 0.6f;
	if (is_pressed(controls, I_RY2))
		isometric->rotation.y += 0.6f;
	if (is_pressed(controls, I_RZ1))
		isometric->rotation.z -= 0.6f;
	if (is_pressed(controls, I_RZ2))
		isometric->rotation.z += 0.6f;
	ft_angle(&isometric->rotation.x);
	ft_angle(&isometric->rotation.y);
	ft_angle(&isometric->rotation.z);
}

static void	zoom(t_isometric *isometric, t_controls controls)
{
	if (is_pressed(controls, I_ZOOM)
		&& isometric->zoom * isometric->zoom_base < width())
		isometric->zoom *= 1.03f;
	if (is_pressed(controls, I_UNZOOM)
		&& isometric->zoom * isometric->zoom_base > 0.3f)
		isometric->zoom *= 0.97f;
}

static void	y_amplifier(t_isometric *isometric, t_controls controls)
{
	if (is_pressed(controls, I_YA1))
		isometric->y_amplifier += 0.25f;
	if (is_pressed(controls, I_YA2))
		isometric->y_amplifier -= 0.25f;
}

void	isometric_key_event(t_fdf *fdf)
{
	t_isometric			*isometric;
	t_controls			controls;

	isometric = &fdf->isometric;
	controls = isometric->controls;
	translations(isometric, controls);
	rotations(isometric, controls);
	zoom(isometric, controls);
	y_amplifier(isometric, controls);
}
