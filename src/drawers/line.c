/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:33:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:56:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_only_points(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		return (fdf->isometric.only_points);
	if (fdf->type == CONIC)
		return (fdf->conic.only_points);
	return (fdf->parallel.only_points);
}

static int	check_depth(t_fdf *fdf, t_pixel_data *new, float v)
{
	int	res;

	new->depth = v;
	res = new->pos.x >= 0 && new->pos.x < width()
		&& new->pos.y >= 0 && new->pos.y < height()
		&& new->depth > fdf->depth[(int)new->pos.y][(int)new->pos.x];
	if (res)
		fdf->depth[(int)new->pos.y][(int)new->pos.x] = new->depth;
	return (res);
}

static void	init_line_data(t_line_data *data, t_vector2 po1, t_vector2 po2)
{
	data->s.x = 1 - (2 * (po1.x >= po2.x));
	data->s.y = 1 - (2 * (po1.y >= po2.y));
	data->delta.x = ft_abs(po1.x - po2.x);
	data->delta.y = -ft_abs(po1.y - po2.y);
	data->e = data->delta.x + data->delta.y;
	data->tot = sqrt((po2.x - po1.x) * (po2.x - po1.x)
			+ (po2.y - po1.y) * (po2.y - po1.y));
	data->step = data->tot / ft_max(data->delta.x, -data->delta.y);
	data->cur = 0.0f;
}

void	process_line(t_fdf *fdf, t_pixel_data p1, t_pixel_data p2)
{
	t_line_data		d;
	t_pixel_data	new;

	init_line_data(&d, p1.pos, p2.pos);
	new.pos = p1.pos;
	while (1)
	{
		if (check_depth(fdf, &new, p1.depth + (d.cur / d.tot)
				* (p2.depth - p1.depth)))
			put_pixel(fdf, new.pos,
				ft_colorbetween(p1.color, p2.color, d.cur, d.tot), 1);
		if ((new.pos.x == p2.pos.x) && (new.pos.y == p2.pos.y))
			break ;
		d.e2 = d.e * 2;
		if (d.e2 >= d.delta.y)
			d.e += d.delta.y;
		if (d.e2 >= d.delta.y)
			new.pos.x += d.s.x;
		if (d.e2 <= d.delta.x)
			d.e += d.delta.x;
		if (d.e2 <= d.delta.x)
			new.pos.y += d.s.y;
		d.cur += d.step;
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int mirror)
{
	t_pixel_data	p1;
	t_pixel_data	p2;

	p1 = get_pdata(fdf, a, mirror);
	p2 = get_pdata(fdf, b, mirror);
	if (!cohen_sutherland_clip(&p1.pos, &p2.pos))
		return ;
	p1.pos.x = ft_ftoi(p1.pos.x);
	p1.pos.y = ft_ftoi(p1.pos.y);
	p2.pos.x = ft_ftoi(p2.pos.x);
	p2.pos.y = ft_ftoi(p2.pos.y);
	if (is_only_points(fdf))
	{
		put_pixel(fdf, p1.pos, p1.color, 1);
		put_pixel(fdf, p2.pos, p2.color, 1);
		return ;
	}
	process_line(fdf, p1, p2);
}
