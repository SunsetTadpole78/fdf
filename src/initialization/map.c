/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/29 10:09:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_points(t_map *map, char ***lines)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			map->points[y][x].pos.x = x;
			map->points[y][x].pos.y = chars_to_float(lines[y][x]);
			map->points[y][x].pos.z = y;
			map->points[y][x].can_mirror = map->points[y][x].pos.y != 0;
			if (ft_strchr(lines[y][x], ','))
				map->points[y][x].color = get_color(lines[y][x]);
			else
				map->points[y][x].color = 0xFFFFFF;
			x++;
		}
		y++;
	}
	map->points[y] = NULL;
}

t_map	*init_map(char ***lines)
{
	t_map	*map;
	int		y;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	set_map_data(lines, map);
	map->points = malloc(sizeof(t_point *) * (map->size.z + 1));
	if (!map->points)
		return (NULL);
	y = 0;
	while (y < map->size.z)
	{
		map->points[y] = malloc(sizeof(t_point) * map->size.x);
		if (!map->points[y])
		{
			while (y > 0)
				free(map->points[--y]);
			free(map->points);
			return (NULL);
		}
		y++;
	}
	create_points(map, lines);
	return (map);
}

t_map	*parse_map(char *path)
{
	int		fd;
	int		y;
	char	***lines;
	char	*line;
	t_map	*map;

	if (!init_lines(path, &lines, &fd))
		return (NULL);
	y = 0;
	while (lines[y])
	{
		y++;
		line = get_next_line(fd);
		if (add_line(line, &lines, y) < 0)
			return (NULL);
	}
	map = init_map(lines);
	free_lines(&lines, y);
	return (map);
}
