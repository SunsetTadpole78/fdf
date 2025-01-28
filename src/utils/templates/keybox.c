/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:43:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 09:35:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keybox_color(t_vector2 v, int w, int h)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	return (dark_gray());
}

int	keybox_color_hover(t_vector2 v, int w, int h, int selected)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	if (selected)
		return (0x2C2C75);
	return (light_gray());
}

int	keybox_color_pressed(t_vector2 v, int w, int h)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	return (0x1C1C4B);
}

void	draw_keybox(t_fdf *fdf, t_button *button)
{
	draw_square(fdf, button);
}
