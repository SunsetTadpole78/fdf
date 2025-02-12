/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:48:21 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 14:49:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_square(t_fdf *fdf, t_button *button)
{
	t_vector2	pos;
	t_vector2	cpos;

	pos.y = button->offset.y;
	cpos.y = 0;
	while (pos.y < (button->size.y + button->offset.y))
	{
		pos.x = button->offset.x;
		cpos.x = 0;
		while (pos.x < (button->size.x + button->offset.x))
		{
			put_pixel(fdf, pos,
				get_button_color(cpos, button, button->size), 1);
			pos.x++;
			cpos.x++;
		}
		pos.y++;
		cpos.y++;
	}
}
