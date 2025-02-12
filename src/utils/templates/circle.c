/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:06:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 15:08:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_outline(t_fdf *fdf, int radius, t_vector2 offset)
{
	int			n;
	double		theta;
	t_vector2	pos;
	int			i;

	i = 0;
	n = ceil(2 * M_PI * radius);
	while (i < n)
	{
		theta = (2 * M_PI / n) * i;
		pos.x = offset.x + cos(theta) * radius;
		pos.y = offset.y + sin(theta) * radius;
		put_pixel(fdf, pos, 0xFFFFFF, 1);
		i++;
	}
}

static void	circle_line(t_vector2 pos, int x2, t_fdf *fdf, t_button *button)
{
	t_vector2	cpos;
	t_vector2	size;

	size = button->size;
	size.x *= 2;
	size.y *= 2;
	while (pos.x <= x2)
	{
		cpos = pos;
		cpos.x -= button->offset.x - button->size.x;
		cpos.y -= button->offset.y - button->size.y;
		put_pixel(fdf, pos, get_button_color(cpos, button, size), 1);
		pos.x++;
	}
}

static int	get_radius(t_button *button)
{
	if (button->size.x > button->size.y)
		return (button->size.x);
	return (button->size.y);
}

void	draw_circle(t_fdf *fdf, t_button *button)
{
	t_vector2	v;
	int			m;
	t_vector2	pos;

	v.x = 0;
	v.y = get_radius(button);
	m = 5 - 4 * v.y;
	while (v.x <= v.y)
	{
		pos.x = button->offset.x - v.x;
		pos.y = button->offset.y - v.y;
		circle_line(pos, button->offset.x + v.x, fdf, button);
		pos.y = button->offset.y + v.y;
		circle_line(pos, button->offset.x + v.x, fdf, button);
		pos.x = button->offset.x - v.y;
		pos.y = button->offset.y - v.x;
		circle_line(pos, button->offset.x + v.y, fdf, button);
		pos.y = button->offset.y + v.x;
		circle_line(pos, button->offset.x + v.y, fdf, button);
		if (m > 0)
			m -= 8 * --v.y;
		m += 8 * ++v.x + 4;
	}
	if (button->selected)
		draw_outline(fdf, get_radius(button), button->offset);
}
