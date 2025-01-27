/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:14:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/23 11:44:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	translate(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Left || keycode == XK_Right)
	{
		fdf->display_data->offset.x += 0.5 * (1 - 2 * (keycode == XK_Left));
		return (1);
	}
	if (keycode == XK_Up || keycode == XK_Down)
	{
		fdf->display_data->offset.y += 0.5 * (1 - 2 * (keycode == XK_Up));
		return (1);
	}
	return (0);
}
