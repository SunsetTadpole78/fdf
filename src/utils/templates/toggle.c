/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:27:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 15:46:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	toggle_color(t_vector2 v, int w, int h)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	return (dark_gray());
}

int	toggle_color_hover(t_vector2 v, int w, int h, int selected)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	if (selected && (v.x >= (w / 4) && v.x < w - (w / 4)) && (v.y >= (h / 4) && v.y < h - (h / 4)))
		return (0xFFFFFF);
	return (light_gray());
}

int	toggle_color_pressed(t_vector2 v, int w, int h)
{
	if (v.x < 2 || v.x >= (w - 2) || v.y < 2 || v.y >= (h - 2))
		return (0x2F2F33);
	if ((v.x >= (w / 4) && v.x < w - (w / 4)) && (v.y >= (h / 4) && v.y < h - (h / 4)))
		return (0xD8D8D8);
	return (gray());
}

void	draw_toggle(t_fdf *fdf, t_button *button)
{
	draw_square(fdf, button);
}
