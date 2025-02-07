/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:45:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/07 17:22:38 by lroussel         ###   ########.fr       */
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

	if (pos.x < 0 || pos.x >= WIDTH || pos.y < 0 || pos.y >= HEIGHT)
		return (0);
	pixel = fdf->img.addr + ((int)pos.y * fdf->img.ll + (int)pos.x * (fdf->img.bpp / 8));
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
	return (v.x < 0 || v.x >= WIDTH || v.y < 0 || v.y >= HEIGHT);
}

int rround(float num) {
    return (int)(num + (num >= 0 ? 0.5f : -0.5f));
}

void	fix_lines(t_vector2 *v, t_vector2 *v2)
{
	float	m;
	float	p;
	
	if (v->x < 0 && v->x < v2->x)
	{
		m = (v2->y - v->y) / (v2->x - v->x);
		p = v2->y - m * v2->x;
		v->y = (m * 0 + p);
		v->x = 0;
	}
	else if (v->x > WIDTH && v->x > v2->x)
	{
		m = (v2->y - v->y) / (v2->x - v->x);
		p = v2->y - m * v2->x;
		v->y = (m * (WIDTH) + p);
		v->x = (WIDTH);
	}
	if (v->y < 0 && v->y < v2->y)
	{
		m = (v2->x - v->x) / (v2->y - v->y);
		p = v2->x - m * v2->y;
		v->x = (m * 0 + p);
		v->y = 0;
	}
	else if (v->y > HEIGHT && v->y > v2->y)
	{
		m = (v2->x - v->x) / (v2->y - v->y);
		p = v2->x - m * v2->y;
		v->x = (m * (HEIGHT) + p);
		v->y = (HEIGHT);
	}
}

int	outside(t_vector2 v, t_vector2 v2)
{
	return ((v.x < 0 && v2.x < 0) || (v.x >= WIDTH && v2.x >= WIDTH)
		|| (v.y < 0 && v2.y < 0) || (v.y >= HEIGHT && v2.y >= HEIGHT));
}

int	black(void)
{
	return (0);
}

void	change_background(t_fdf *fdf, int (color)(t_vector2, int, int, int))
{
	t_background	*bg;
	char	*pixel;
	
	bg = fdf->background;
	bg->bg_color = color;
	if (!color)
		return ;
	if (!bg->bg.img)
		bg->bg.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	bg->bg.addr = mlx_get_data_addr(bg->bg.img, &bg->bg.bpp, &bg->bg.ll, &bg->bg.endian);
	t_vector2	pos;
	pos.y = 0;
	while (pos.y <= HEIGHT)
	{
		pos.x = 0;
		while (pos.x <= WIDTH)
		{
			pixel = fdf->background->bg.addr + ((int)pos.y * fdf->img.ll + (int)pos.x * (fdf->img.bpp / 8));
			*(unsigned int *)pixel = color(pos, WIDTH, HEIGHT, 0);
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
		HEIGHT * fdf->img.ll + WIDTH * (fdf->img.bpp / 8)
	);
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

int	ft_max(int v, int v2)
{
	if (v > v2)
		return (v);
	return v2;
}

t_pixel_data	pixel_pos(t_fdf *fdf, t_vector3 v3, int  mirror)
{
	t_pixel_data (*pos)(t_fdf *, t_vector3, int);

	pos = fdf->pixel_pos;
	return (pos(fdf, v3, mirror));
}

void	draw_points(t_fdf *fdf, t_vector2 p1, int c1, t_vector2 p2, int c2)
{
	put_pixel(fdf, p1, c1, 1);
	put_pixel(fdf, p2, c2, 1);
}

void	algo(t_fdf *fdf, t_vector2 po1, t_vector2 po2, int d1, int d2, int ca, int cb)
{
	float	dx;
	float	dy;
	float	e;
	float	sx;
	float	sy;
	float	e2;
	t_pixel_data	new;
	float		total;
	float		current;
	float	depth;
	sx = -1;
	if (po1.x < po2.x)
		sx = 1;
	sy = -1;
	if (po1.y < po2.y)
		sy = 1;
	dx = ft_abs(po1.x - po2.x);
	dy = -ft_abs(po1.y - po2.y);
	e = dx + dy;
	total = sqrt((po2.x - po1.x) * (po2.x - po1.x)
			+ (po2.y - po1.y) * (po2.y - po1.y));
	new.pos = po1;
	while (1)
	{
		current = sqrt((new.pos.x - po1.x) * (new.pos.x - po1.x)
				+ (new.pos.y - po1.y) * (new.pos.y - po1.y));
		depth = d1 + (current / total) * (d2 - d1);
		if (new.pos.x >= 0 && new.pos.x < WIDTH && new.pos.y >= 0 && new.pos.y < HEIGHT) {
			if (depth > fdf->depth[(int)new.pos.y][(int)new.pos.x]) {
        			put_pixel(fdf, new.pos, color_between(ca, cb, current, total), 1);
        			fdf->depth[(int)new.pos.y][(int)new.pos.x] = depth;
   			}
		}

		if ((new.pos.x == po2.x) && (new.pos.y == po2.y))
			break ;
		e2 = e * 2;
		if (e2 >= dy)
			e += dy;
		if (e2 >= dy)
			new.pos.x += sx;
		if (e2 <= dx)
			e += dx;
		if (e2 <= dx)
			new.pos.y += sy;
	}
}

void	draw_line(t_fdf *fdf, t_point a, t_point b, int mirror)
{(void)mirror;
	t_pixel_data	p1;
	t_pixel_data	p2;
	t_vector2	po1;
	t_vector2	po2;
	p1 = pixel_pos(fdf, a.pos, mirror);
	po1 = p1.pos;
	p2 = pixel_pos(fdf, b.pos, mirror);
	po2 = p2.pos;
	if (outside(po1, po2))
		return ;
	if (!cohenSutherlandClip(&po1, &po2) || outside(po1, po2))
		return ;
	po1.x = rround(po1.x);
	po1.y = rround(po1.y);
	po2.x = rround(po2.x);
	po2.y = rround(po2.y);
	if (fdf->only_points)
	{
		put_pixel(fdf, po1, a.color, 1);
		put_pixel(fdf, po2, b.color, 1);
		return ;
	}
	algo(fdf, po1, po2, p1.depth, p2.depth, a.color, b.color);
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

	if (fdf->type == CONIC || (fdf->type == ISOMETRIC && !fdf->isometric.axis)
	|| (fdf->type == PARALLEL && !fdf->parallel.axis))
		return ;
	m_y = ((fdf->map->max_y) + (fdf->map->min_y)) / 2;
	o.x = (fdf->map->size.x - 1) / 2;
	o.y = m_y;
	o.z = (fdf->map->size.z - 1) / 2;
	x = o;
	x.x = 1000000;
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

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	t_map	*map;

	clear_depth(fdf);
	draw_background(fdf);
	draw_background(fdf);
	map = fdf->map;
	y = 0;
	while (map->points[y])
	{
		x = 0;
		while (x < map->size.x)
		{
			if (x + 1 < map->size.x)
			{
				if (map->points[y][x].pos.x == x && map->points[y][x + 1].pos.x == x + 1)
				{
						draw_line(fdf, map->points[y][x], map->points[y][x + 1], 0);
					if (fdf->isometric.mirror && (map->points[y][x].can_mirror || map->points[y][x + 1].can_mirror))
						draw_line(fdf, map->points[y][x], map->points[y][x + 1], 1);
				}
			}
			if (map->points[y + 1])
			{
				if (map->points[y][x].pos.x == x && map->points[y + 1][x].pos.x == x)
				{
						draw_line(fdf, map->points[y][x], map->points[y + 1][x], 0);
					if (fdf->isometric.mirror && (map->points[y][x].can_mirror || map->points[y + 1][x].can_mirror))
						draw_line(fdf, map->points[y][x], map->points[y + 1][x], 1);
				}
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
	f(fdf);
	fdf->screen.x = get_resolution()[1];
	fdf->screen.y = get_resolution()[0];
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.ll, &fdf->img.endian);
	fdf->map = map;
	fdf->pivot_point.x = fdf->map->size.x / 2;
	fdf->pivot_point.y = fdf->map->size.y / 2;
	fdf->pivot_point.z = fdf->map->size.z / 2;
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
	return (fdf);
}
