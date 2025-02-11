/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:17:02 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:19:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translations(t_parallel *parallel, t_c controls)
{
	if (is_pressed(controls, P_UP))
		parallel->offset.y -= 0.1f;
	if (is_pressed(controls, P_DOWN))
		parallel->offset.y += 0.1f;
	if (is_pressed(controls, P_LEFT))
		parallel->offset.x -= 0.1f;
	if (is_pressed(controls, P_RIGHT))
		parallel->offset.x += 0.1f;
}

void	rotate_parallel(t_parallel *parallel, t_c controls, int keycode)
{
	t_key	*key;

	key = get_key_with_code(controls, keycode);
	if (!key)
		return ;
	if (key->id == P_RX1)
		parallel->rotation.x = ((int)parallel->rotation.x + 1) % 4;
	else if (key->id == P_RX2)
		parallel->rotation.x = ((int)parallel->rotation.x - 1 + 4) % 4;
	else if (key->id == P_RY1)
		parallel->rotation.y = ((int)parallel->rotation.y + 1) % 4;
	else if (key->id == P_RY2)
		parallel->rotation.y = ((int)parallel->rotation.y - 1 + 4) % 4;
}

static void	zoom(t_parallel *parallel, t_c controls)
{
	if (is_pressed(controls, P_ZOOM)
		&& parallel->zoom * parallel->zoom_base < width())
		parallel->zoom *= 1.03f;
	if (is_pressed(controls, P_UNZOOM)
		&& parallel->zoom * parallel->zoom_base > 0.3f)
		parallel->zoom *= 0.97f;
}

static void	y_amplifier(t_parallel *parallel, t_c controls)
{
	if (is_pressed(controls, P_YA1))
		parallel->y_amplifier += 0.25f;
	if (is_pressed(controls, P_YA2))
		parallel->y_amplifier -= 0.25f;
}

void	parallel_key_event(t_fdf *fdf)
{
	t_parallel	*parallel;
	t_c			controls;

	parallel = &fdf->parallel;
	controls = parallel->controls;
	translations(parallel, controls);
	zoom(parallel, controls);
	y_amplifier(parallel, controls);
}
