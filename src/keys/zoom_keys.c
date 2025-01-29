/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:16:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 09:45:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom_check(int keycode, t_fdf *fdf)
{
	if (keycode == fdf->controls.zoom.v || keycode == fdf->controls.unzoom.v)
	{
		if (fdf->display_data->zoom * fdf->display_data->zoom_v >= WIDTH
			&& keycode == fdf->controls.zoom.v)
			return (0);
		if (fdf->display_data->zoom * fdf->display_data->zoom_v <= 0.3
			&& keycode == fdf->controls.unzoom.v)
			return (0);
		fdf->display_data->zoom *= 1.0 + 0.05 * (keycode == fdf->controls.zoom.v)
			- 0.05 * (keycode == fdf->controls.unzoom.v);
		return (1);
	}
	return (0);
}
