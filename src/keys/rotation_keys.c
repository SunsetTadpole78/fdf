/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 09:49:21 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == fdf->controls.reduce_x.v || keycode == fdf->controls.add_x.v)
	{
		fdf->display_data->rotate.x += 1 * (1 - 2 * (keycode == fdf->controls.reduce_x.v));
		return (1);
	}
	if (keycode == fdf->controls.reduce_y.v || keycode == fdf->controls.add_y.v)
	{
		fdf->display_data->rotate.y += 1 * (1 - 2 * (keycode == fdf->controls.reduce_y.v));
		return (1);
	}
	if (keycode == fdf->controls.reduce_z.v || keycode == fdf->controls.add_z.v)
	{
		fdf->display_data->rotate.z += 1 * (1 - 2 * (keycode == fdf->controls.add_z.v));
		return (1);
	}
	return (0);
}
