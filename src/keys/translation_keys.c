/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:14:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 09:44:38 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	translate(int keycode, t_fdf *fdf)
{
	if (keycode == fdf->controls.left.v || keycode == fdf->controls.right.v)
	{
		fdf->display_data->offset.x += 0.5 * (1 - 2 * (keycode == fdf->controls.left.v));
		return (1);
	}
	if (keycode == fdf->controls.up.v || keycode == fdf->controls.down.v)
	{
		fdf->display_data->offset.y += 0.5 * (1 - 2 * (keycode == fdf->controls.up.v));
		return (1);
	}
	return (0);
}
