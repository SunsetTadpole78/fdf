/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:49:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/06 16:38:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel_data	pos(t_vector3 v3, float zoom)
{
	t_vector2	v2;
	t_pixel_data	data;

	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;
	v3.x += 0.5 * zoom;
	v3.z += 0.5 * zoom;
	v2.x = WIDTH / 2 + (v3.x - v3.z) * cos(30 * (M_PI / 180));
	v2.y = 2 + HEIGHT / 2 + (v3.x + v3.z) * sin(30 * (M_PI / 180)) - v3.y;
	v2.x -= 915;
	v2.y -= 502;
	data.pos = v2;
	data.depth = v3.z;
	return (data);
}

static int	gc(t_vector3 v, int (color)(t_vector3, t_vector2, t_vector3))
{
	t_vector2	mimay;
	t_vector3	size;

	mimay.x = 0;
	mimay.y = 1;
	size.x = 2;
	size.y = 2;
	size.z = 2;
	return (color(v, mimay, size));
}

static void	dr(t_fdf *fdf, t_vector3 v, t_vector3 v2, t_button *button)
{
	t_pixel_data	d1;
	t_pixel_data	d2;

	d1 = pos(v, button->size.x);
	d2 = pos(v2, button->size.x);
	d1.pos.x = (int)d1.pos.x + button->offset.x - button->size.x;
	d1.pos.y = (int)d1.pos.y + button->offset.y - button->size.y;
	d2.pos.x = (int)d2.pos.x + button->offset.x - button->size.x;
	d2.pos.y = (int)d2.pos.y + button->offset.y - button->size.y;
	algo(fdf, d1.pos, d2.pos, d1.depth * 100, d2.depth * 100, gc(v, button->color), gc(v2, button->color));	
}

void	draw_cube(t_fdf *fdf, t_button *button)
{(void)button;
	dr(fdf, (t_vector3){0, 0, 0}, (t_vector3){1, 0, 0}, button);
	dr(fdf, (t_vector3){0, 0, 0}, (t_vector3){0, 1, 0}, button);
	dr(fdf, (t_vector3){0, 1, 0}, (t_vector3){1, 1, 0}, button);
	dr(fdf, (t_vector3){1, 0, 0}, (t_vector3){1, 1, 0}, button);
	
	dr(fdf, (t_vector3){0, 0, 1}, (t_vector3){1, 0, 1}, button);
	dr(fdf, (t_vector3){0, 0, 1}, (t_vector3){0, 1, 1}, button);
	dr(fdf, (t_vector3){0, 1, 1}, (t_vector3){1, 1, 1}, button);
	dr(fdf, (t_vector3){1, 0, 1}, (t_vector3){1, 1, 1}, button);

	dr(fdf, (t_vector3){0, 0, 0}, (t_vector3){0, 0, 1}, button);
	dr(fdf, (t_vector3){0, 1, 0}, (t_vector3){0, 1, 1}, button);
	dr(fdf, (t_vector3){1, 0, 0}, (t_vector3){1, 0, 1}, button);
	dr(fdf, (t_vector3){1, 1, 0}, (t_vector3){1, 1, 1}, button);
}
