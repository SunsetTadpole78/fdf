/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:42:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/06 16:26:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	c_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (-1);
}

static int	is_hex(char *value)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != ' ' && value[i] != '\n')
	{
		if (c_hex(value[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

static int	char_to_hex(char *value)
{
	int	res;
	int	i;

	res = 0;
	i = 2;
	while (value[i] && value[i] != ' ' && value[i] != '\n')
	{
		res = res * 16 + c_hex(value[i]);
		i++;
	}
	return (res);
}

int	get_color(char *el)
{
	char	**splited;
	char	*color;
	int		i;
	int		v;

	splited = ft_split(el, ',');
	if (!splited || !splited[1])
		return (0xFFFFFF);
	color = ft_strdup(splited[1]);
	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
	if (!color[0] || color[0] != '0' || !color[1]
		|| color[1] != 'x' || !is_hex(color + 2))
		return (0xFFFFFF);
	v = char_to_hex(color);
	free(color);
	return (v);
}

t_rgb	to_rgb(int v)
{
	t_rgb	rgb;

	rgb.t = (v >> 24) & 0xFF;
	rgb.r = (v >> 16) & 0xFF;
	rgb.g = (v >> 8) & 0xFF;
	rgb.b = v & 0xFF;
	return (rgb);
}

int	from_rgb(t_rgb rgb)
{
	return (rgb.t << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}

int	min(int v, int v2)
{
	if (v < v2)
		return (v);
	return (v2);
}

int	max(int v, int v2)
{
	if (v > v2)
		return (v);
	return (v2);
}

int	color_between(int ca, int cb, float v, float t)
{
	t_rgb	rgb1;	
	t_rgb	rgb2;
	t_rgb	between;

	rgb1 = to_rgb(ca);
	rgb2 = to_rgb(cb);
	between.t = rgb1.t + (v / t * (rgb2.t - rgb1.t));
	between.r = rgb1.r + (v / t * (rgb2.r - rgb1.r));
	between.g = rgb1.g + (v / t * (rgb2.g - rgb1.g));
	between.b = rgb1.b + (v / t * (rgb2.b - rgb1.b));
	return (from_rgb(between));
}

void	update_colors(t_fdf *fdf, int (color)(t_vector3, t_vector2, t_vector3))
{
	size_t	y;
	size_t	x;
	t_point	**points;
	t_vector2	mimay;

	y = 0;
	points = fdf->map->points;
	mimay.x = fdf->map->min_y;
	mimay.y = fdf->map->max_y;
	while (points[y])
	{
		x = 0;
		while (x < fdf->map->size.x)
		{
			if (!points[y][x].hardcoded_color)
				points[y][x].color = color(points[y][x].pos, mimay, fdf->map->size);
			x++;
		}
		y++;
	}
}
