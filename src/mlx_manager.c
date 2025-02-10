/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:45:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 10:45:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	call(int (color)(t_vector2, int, int, int), t_vector2 cpos,
	t_button *button, t_vector2 size)
{
	return (color(cpos, size.x, size.y, button->selected));
}

int	get_button_color(t_vector2 cpos, t_button *button, t_vector2 size)
{
	void	*color;

	if (button->hover)
		color = button->hover_color;
	else if (button->selected)
		color = button->pressed_color;
	else
		color = button->color;
	return (call(color, cpos, button, size));
}

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha)
{
	char	*pixel;

	if (pos.x < 0 || pos.x >= width() || pos.y < 0 || pos.y >= height())
		return (0);
	pixel = fdf->img.addr + ((int)pos.y * fdf->img.ll
			+ (int)pos.x * (fdf->img.bpp / 8));
	if (alpha < 1 && pixel != 0)
		color = color_between(*(unsigned int *)pixel, color, alpha, 1);
	*(unsigned int *)pixel = color;
	return (1);
}

int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

int	outside_p(t_vector2 v)
{
	return (v.x < 0 || v.x >= width() || v.y < 0 || v.y >= height());
}

int	rround(float num)
{
	if (num >= 0)
		return ((int)(num + 0.5f));
	return ((int)(num - 0.5f));
}

int	outside(t_vector2 v, t_vector2 v2)
{
	return ((v.x < 0 && v2.x < 0) || (v.x >= width() && v2.x >= width())
		|| (v.y < 0 && v2.y < 0) || (v.y >= height() && v2.y >= height()));
}

int	black(void)
{
	return (0);
}

void	change_background(t_fdf *fdf, int (color)(t_vector2, int, int, int))
{
	t_background	*bg;
	char			*pixel;
	t_vector2		pos;

	bg = fdf->background;
	bg->bg_color = color;
	if (!color)
		return ;
	if (!bg->bg.img)
		bg->bg.img = mlx_new_image(fdf->mlx, width(), height());
	bg->bg.addr = mlx_get_data_addr(bg->bg.img, &bg->bg.bpp,
			&bg->bg.ll, &bg->bg.endian);
	pos.y = 0;
	while (pos.y <= height())
	{
		pos.x = 0;
		while (pos.x <= width())
		{
			pixel = fdf->background->bg.addr
				+ ((int)pos.y * fdf->img.ll + (int)pos.x * (fdf->img.bpp / 8));
			*(unsigned int *)pixel = color(pos, width(), height(), 0);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_background(t_fdf *fdf)
{
	if (!fdf->background->bg_color)
		return ;
	ft_memcpy(
		fdf->img.addr,
		fdf->background->bg.addr,
		height() * fdf->img.ll + width() * (fdf->img.bpp / 8));
}

void	circle_line(t_vector2 pos, int x2, t_fdf *fdf, t_button *button)
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

void	draw_circle(t_fdf *fdf, int radius, t_button *button)
{
	int			x;
	int			y;
	int			m;
	t_vector2	pos;

	x = 0;
	y = radius;
	m = 5 - 4 * radius;
	while (x <= y)
	{
		pos.x = button->offset.x - x;
		pos.y = button->offset.y - y;
		circle_line(pos, button->offset.x + x, fdf, button);
		pos.y = button->offset.y + y;
		circle_line(pos, button->offset.x + x, fdf, button);
		pos.x = button->offset.x - y;
		pos.y = button->offset.y - x;
		circle_line(pos, button->offset.x + y, fdf, button);
		pos.y = button->offset.y + x;
		circle_line(pos, button->offset.x + y, fdf, button);
		if (m > 0)
			m -= 8 * --y;
		m += 8 * ++x + 4;
	}
}

void	outline(t_fdf *fdf, int radius, t_vector2 offset)
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

int	ft_max(int v, int v2)
{
	if (v > v2)
		return (v);
	return (v2);
}

t_pixel_data	pixel_pos(t_fdf *fdf, t_point p, int mirror)
{
	t_pixel_data	data;

	t_pixel_data (*pos)(t_fdf *, t_vector3, int);
	pos = fdf->pixel_pos;
	data = pos(fdf, p.pos, mirror);
	data.color = p.color;
	return (data);
}

int	check_depth(t_fdf *fdf, t_pixel_data *new, float v)
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

void	init_line_data(t_line_data *data, t_vector2 po1, t_vector2 po2)
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

void	algo(t_fdf *fdf, t_pixel_data p1, t_pixel_data p2)
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
				color_between(p1.color, p2.color, d.cur, d.tot), 1);
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

	p1 = pixel_pos(fdf, a, mirror);
	p2 = pixel_pos(fdf, b, mirror);
	if (outside(p1.pos, p2.pos))
		return ;
	if (!cohenSutherlandClip(&p1.pos, &p2.pos) || outside(p1.pos, p2.pos))
		return ;
	p1.pos.x = rround(p1.pos.x);
	p1.pos.y = rround(p1.pos.y);
	p2.pos.x = rround(p2.pos.x);
	p2.pos.y = rround(p2.pos.y);
	if (fdf->only_points)
	{
		put_pixel(fdf, p1.pos, p1.color, 1);
		put_pixel(fdf, p2.pos, p2.color, 1);
		return ;
	}
	algo(fdf, p1, p2);
}

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

void	draw_button(t_fdf *fdf, t_button *button)
{
	int		radius;

	if (button->type == CIRCLE)
	{
		if (button->size.x > button->size.y)
			radius = button->size.x;
		else
			radius = button->size.y;
		draw_circle(fdf, radius, button);
		if (button->selected)
			outline(fdf, radius, button->offset);
	}
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

void	draw_and_mirror(t_fdf *fdf, t_point p1, t_point p2)
{
	draw_line(fdf, p1, p2, 0);
	if (fdf->isometric.mirror && (p1.can_mirror || p2.can_mirror))
		draw_line(fdf, p1, p2, 1);
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	t_map	*map;
	t_point	p;

	map = fdf->map;
	y = 0;
	while (map->points[y])
	{
		x = 0;
		while (x < map->size.x)
		{
			p = map->points[y][x];
			if (x + 1 < map->size.x && p.pos.x == x
				&& map->points[y][x + 1].pos.x == x + 1)
				draw_and_mirror(fdf, p, map->points[y][x + 1]);
			if (map->points[y + 1] && p.pos.x == x
				&& map->points[y + 1][x].pos.x == x)
				draw_and_mirror(fdf, p, map->points[y + 1][x]);
			x++;
		}
		y++;
	}
}

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	f(fdf);
	fdf->screen.x = get_resolution()[0];
	fdf->screen.y = get_resolution()[1];
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, width(), height(), "FdF");
	fdf->img.img = mlx_new_image(fdf->mlx, width(), height());
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.ll, &fdf->img.endian);
	fdf->waiting.step = 3;
	fdf->waiting.total = 3;
	return (fdf);
}

void	init_data(t_fdf *fdf, t_map *map)
{
	fdf->map = map;
	fdf->pivot_point.x = fdf->map->size.x / 2.0f;
	fdf->pivot_point.y = fdf->map->size.y / 2.0f;
	fdf->pivot_point.z = fdf->map->size.z / 2.0f;
	init_backgrounds(fdf);
	init_isometric(fdf);
	init_conic(fdf);
	init_parallel(fdf);
	fdf->type = ISOMETRIC;
	fdf->pixel_pos = ipp;
	fdf->must_update = 0;
	fdf->only_points = 0;
	fdf->edit_key = NULL;
	init_navbar(fdf);
	init_depth(fdf);
}
