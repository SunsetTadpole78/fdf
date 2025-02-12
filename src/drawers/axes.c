/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:32:59 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 15:33:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_axe(t_fdf *fdf, t_vector3 o, int type, int color)
{
	t_point		p;
	t_point		p2;

	p.color = color;
	p.can_mirror = 0;
	p.pos = o;
	p2 = p;
	if (type == 0)
		p2.pos.x = 1000000;
	else if (type == 1)
		p2.pos.y = 1000000;
	else if (type == 2)
		p2.pos.z = 1000000;
	draw_line(fdf, p, p2, 0);
}

void	draw_axes(t_fdf *fdf)
{
	float		m_y;
	t_vector3	o;

	if (fdf->type == CONIC || (fdf->type == ISOMETRIC && !fdf->isometric.axis)
		|| (fdf->type == PARALLEL && !fdf->parallel.axis))
		return ;
	m_y = ((fdf->map->max_y) + (fdf->map->min_y)) / 2;
	o.x = (fdf->map->size.x - 1) / 2;
	o.y = m_y;
	o.z = (fdf->map->size.z - 1) / 2;
	draw_axe(fdf, o, 0, 0xFF0000);
	draw_axe(fdf, o, 1, 0x00FF00);
	draw_axe(fdf, o, 2, 0x0000FF);
	return ;
}
