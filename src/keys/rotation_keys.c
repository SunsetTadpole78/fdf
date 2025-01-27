/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/22 12:12:48 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == XK_t || keycode == XK_y)
	{
		fdf->display_data->rotate.x += 1 * (1 - 2 * (keycode == XK_t));
		return (1);
	}
	if (keycode == XK_u || keycode == XK_i)
	{
		fdf->display_data->rotate.y += 1 * (1 - 2 * (keycode == XK_u));
		return (1);
	}
	if (keycode == XK_o || keycode == XK_p)
	{
		fdf->display_data->rotate.z += 1 * (1 - 2 * (keycode == XK_o));
		return (1);
	}
	return (0);
}
