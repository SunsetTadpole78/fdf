/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*init_point(char ***lines, t_vector2 p)
{
	t_point	*point;

	if (!lines[(size_t)p.y] || !lines[(size_t)p.y][(size_t)p.x])
		return (NULL);
	point = malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->pos.x = p.x;
	point->pos.y = chars_to_float(lines[(size_t)p.y][(size_t)p.x]);
	point->pos.z = p.y;
	return (point);
}

int	init_points(t_map *map, char ***lines)
{
	size_t	x;
	size_t	y;
	t_line	*line;

	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			line = build_line(lines, vector2(x, y), vector2(x, y + 1));
			if (!line && lines[y + 1] && lines[y + 1][x])
				return (0);
			add_to_map(map, line);
			line = build_line(lines, vector2(x, y), vector2(x + 1, y));
			if (!line && lines[y] && lines[y][x + 1])
				return (0);
			add_to_map(map, line);
			x++;
		}
		y++;
	}
	return (1);
}
