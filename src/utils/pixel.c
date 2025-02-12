/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:33:25 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:32:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha)
{
	unsigned int	*v;

	if (pos.x < 0 || pos.x >= width() || pos.y < 0 || pos.y >= height())
		return (0);
	v = &(((unsigned int *)fdf->img.addr)[(int)pos.y * width() + (int)pos.x]);
	if (alpha < 1 && *v != 0)
		*v = ft_colorbetween(*v, color, alpha, 1);
	else
		*v = color;
	return (1);
}

int	is_outside(t_vector2 v)
{
	return (v.x < 0 || v.x >= width() || v.y < 0 || v.y >= height());
}

t_pixel_data	get_pdata(t_fdf *fdf, t_point p, int mirror)
{
	t_pixel_data	data;

	t_pixel_data (*pos)(t_fdf *, t_vector3, int);
	pos = fdf->position_adr;
	data = pos(fdf, p.pos, mirror);
	data.color = p.color;
	return (data);
}
