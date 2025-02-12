/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:52 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 16:00:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_button(t_fdf *fdf, t_button *button)
{
	if (button->type == CIRCLE)
		draw_circle(fdf, button);
	else if (button->type == NAVBAR)
		draw_square(fdf, button);
	else if (button->type == TOGGLE)
		draw_toggle(fdf, button);
	else if (button->type == KEYBOX)
		draw_keybox(fdf, button);
	else if (button->type == CUBE)
		draw_cube(fdf, button);
}

void	draw_buttons(t_fdf *fdf, t_button **buttons)
{
	int	i;

	i = 0;
	while (buttons[i])
	{
		draw_button(fdf, buttons[i]);
		i++;
	}
}
