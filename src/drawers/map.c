/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:33:13 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:43:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_and_mirror(t_fdf *fdf, t_point p1, t_point p2, int mirror)
{
	draw_line(fdf, p1, p2, 0);
	if (mirror && (p1.can_mirror || p2.can_mirror))
		draw_line(fdf, p1, p2, 1);
}

static int	is_mirror(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		return (fdf->isometric.mirror);
	if (fdf->type == CONIC)
		return (fdf->conic.mirror);
	return (fdf->parallel.mirror);
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	t_map	*map;
	t_point	p;
	int		mirror;

	mirror = is_mirror(fdf);
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
				draw_and_mirror(fdf, p, map->points[y][x + 1], mirror);
			if (map->points[y + 1] && p.pos.x == x
				&& map->points[y + 1][x].pos.x == x)
				draw_and_mirror(fdf, p, map->points[y + 1][x], mirror);
			x++;
		}
		y++;
	}
}
