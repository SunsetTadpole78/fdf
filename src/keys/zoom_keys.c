/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:16:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 10:34:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == XK_minus || keycode == XK_equal)
	{
		if (fdf->display_data->zoom * fdf->display_data->zoom_v >= WIDTH
			&& keycode == XK_equal)
			return (0);
		if (fdf->display_data->zoom * fdf->display_data->zoom_v <= 0.3
			&& keycode == XK_minus)
			return (0);
		fdf->display_data->zoom *= 1.0 + 0.05 * (keycode == XK_equal)
			- 0.05 * (keycode == XK_minus);
		return (1);
	}
	return (0);
}
