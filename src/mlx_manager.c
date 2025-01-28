/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:45:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 09:41:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	call(int (color)(t_vector2, int, int, int), t_vector2 cpos, t_button *button, t_vector2 size)
{
	return color(cpos, size.x, size.y, button->selected);
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
	return call(color, cpos, button, size);
}

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha)
{
	char	*pixel;

	if (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT)
		return (0);
	pixel = fdf->addr + ((int)pos.y * fdf->ll + (int)pos.x * (fdf->bpp / 8));
	if (alpha < 1 && pixel != 0)
		color = color_between(*(unsigned int *)pixel, color, alpha, 1);
	*(unsigned int *)pixel = color;
	return (1);
}

void	rotate_x(t_fdf *fdf, t_vector3 *v3)
{
	int		tmp;
	float	alpha;

	alpha = fdf->display_data->rotate.x * (M_PI / 180);
	tmp = v3->y;
	v3->y = tmp * cos(alpha) - v3->z * sin(alpha);
	v3->z = tmp * sin(alpha) + v3->z * cos(alpha);
}

void	rotate_y(t_fdf *fdf, t_vector3 *v3)
{
	int		tmp;
	float	tetha;

	tetha = fdf->display_data->rotate.y * (M_PI / 180);
	tmp = v3->x;
	v3->x = tmp * cos(tetha) + v3->z * sin(tetha);
	v3->z = v3->z * cos(tetha) - tmp * sin(tetha);
}

void	rotate_z(t_fdf *fdf, t_vector3 *v3)
{
	int		tmp;
	float	gamma;

	gamma = fdf->display_data->rotate.z * (M_PI / 180);
	tmp = v3->x;
	v3->x = tmp * cos(gamma) - v3->y * sin(gamma);
	v3->y = tmp * sin(gamma) + v3->y * cos(gamma);
}

t_vector2	pixel_pos(t_fdf *fdf, t_vector3 v3, int  mirror)
{
	t_vector2	v2;
	float		zoom;

	zoom = fdf->display_data->zoom * fdf->display_data->zoom_v;
	if (mirror)
		v3.y *= -1;
	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;
	v3.x -= fdf->display_data->pivot_point.x * zoom;
	v3.y -= fdf->display_data->pivot_point.y * zoom;
	v3.z -= fdf->display_data->pivot_point.z * zoom;
	v3.x += 0.5 * zoom;
	v3.z += 0.5 * zoom;
	rotate_x(fdf, &v3);
	rotate_y(fdf, &v3);
	rotate_z(fdf, &v3);
	v2.x = WIDTH / 2 + (v3.x - v3.z) * cos(30 * (M_PI / 180));
	v2.y = 2 + HEIGHT / 2 + (v3.x + v3.z) * sin(30 * (M_PI / 180)) - v3.y;
	v2.x += fdf->display_data->offset.x * 60;
	v2.y += fdf->display_data->offset.y * 60;
	return (v2);
}

int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

int	outside_p(t_vector2 v)
{
	return (v.x < 0 || v.x > WIDTH || v.y < 0 || v.y > HEIGHT);
}

int	outside(t_vector2 v, t_vector2 v2)
{
	return ((v.x < 0 && v2.x < 0) || (v.x > WIDTH && v2.x > WIDTH)
		|| (v.y < 0 && v2.y < 0) || (v.y > HEIGHT && v2.y > HEIGHT));
}

int	black(void)
{
	return (0);
}

void	background(t_fdf *fdf, int (color)(t_vector2, int, int, int))
{
	t_vector2	pos;

	pos.y = 0;
	while (pos.y <= HEIGHT)
	{
		pos.x = 0;
		while (pos.x <= WIDTH)
		{
			put_pixel(fdf, pos, color(pos, WIDTH, HEIGHT, 0), 1);
			pos.x++;
		}
		pos.y++;
	}
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
	int	x;
	int	y;
	int	m;
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
		{
			y--;
			m -= 8 * y;
		}
		x++;
		m += 8 * x + 4;
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

void	draw_line(t_fdf *fdf, t_point a, t_point b, int mirror)
{
	t_vector2	p1;
	t_vector2	p2;
	float		dx;
	float		dy;
	float		sx;
	float		sy;
	float		error;
	float		e2;
	int			ca;
	int			cb;
	t_vector2	new;
	float		total;
	float		current;

	p1 = pixel_pos(fdf, a.pos, mirror);
	p2 = pixel_pos(fdf, b.pos, mirror);
	if (outside(p1, p2))
		return ;
	dx = ft_abs(p2.x - p1.x);
	sx = -1;
	if (p1.x < p2.x)
		sx = 1;
	dy = -ft_abs(p2.y - p1.y);
	sy = -1;
	if (p1.y < p2.y)
		sy = 1;
	error = dx + dy;
	ca = a.color;
	cb = b.color;
	new = p1;
	(void)ca;
	(void)cb;
	put_pixel(fdf, p1, ca, 1);
	put_pixel(fdf, p2, ca, 1);
	total = sqrt((p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y));
	while (1)
	{
		current = sqrt((new.x - p1.x) * (new.x - p1.x)
				+ (new.y - p1.y) * (new.y - p1.y));
		if (current >= total)
			break ;
		put_pixel(fdf, new, color_between(ca, cb, current, total), 1);
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if ((p1.x <= p2.x && (new.x >= p2.x || new.x > WIDTH))
				|| (p1.x >= p2.x && (new.x <= p2.x || new.x < 0)))
				break ;
			error += dy;
			new.x += sx;
		}
		else if (e2 <= dx)
		{
			if ((p1.y <= p2.y && (new.y >= p2.y || new.y > HEIGHT))
				|| (p1.y >= p2.y && (new.y <= p2.y || new.y < 0)))
				break ;
			error += dx;
			new.y += sy;
		}
	}
}

void	draw_axes(t_fdf *fdf)
{
	float		m_y;
	t_vector3	o;
	t_vector3	x;
	t_vector3	y;
	t_vector3	z;
	t_point		p;
	t_point		p2;

	if (!fdf->display_data->axis)
		return ;

	m_y = ((float)fdf->map->max_y + (float)fdf->map->min_y) / 2;
	o.x = fdf->map->size.x / 2 - 0.5;
	o.y = m_y;
	o.z = fdf->map->size.z / 2 - 0.5;
	x = o;
	x.x = 10000000;
	y = o;
	y.y = x.x;
	z = o;
	z.z = x.x;
	p.pos = o;
	p.color = 0xFF0000;
	p.can_mirror = 0;
	p2 = p;
	p2.pos = x;
	draw_line(fdf, p, p2, 0);
	p.color = 0x00FF00;
	p2.color = 0x00FF00;
	p2.pos = y;
	draw_line(fdf, p, p2, 0);
	p.color = 0x0000FF;
	p2.color = 0x0000FF;
	p2.pos = z;
	draw_line(fdf, p, p2, 0);
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
			put_pixel(fdf, pos, get_button_color(cpos, button, button->size), 1);
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

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	t_map	*map;

	if (fdf->display_data->bg)
		background(fdf, fdf->display_data->bg);
	map = fdf->map;
	y = 0;
	while (map->points[y])
	{
		x = 0;
		while (x < map->size.x)
		{
			if (x + 1 < map->size.x)
			{
				draw_line(fdf, map->points[y][x], map->points[y][x + 1], 0);
				if (fdf->display_data->mirror && (map->points[y][x].can_mirror || map->points[y][x + 1].can_mirror))
					draw_line(fdf, map->points[y][x], map->points[y][x + 1], 1);
			}
			if (map->points[y + 1])
			{
				draw_line(fdf, map->points[y][x], map->points[y + 1][x], 0);
				if (fdf->display_data->mirror && (map->points[y][x].can_mirror || map->points[y + 1][x].can_mirror))
					draw_line(fdf, map->points[y][x], map->points[y + 1][x], 1);
			}
			x++;
		}
		y++;
	}
	draw_axes(fdf);
	draw_navbar(fdf);
}

t_fdf	*create_window(t_map *map)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->ll, &fdf->endian);
	fdf->map = map;
	init_display_data(fdf);
	init_controls(fdf);
	fdf->must_update = 0;
	init_navbar(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	update_buttons_texts(fdf);
	return (fdf);
}
