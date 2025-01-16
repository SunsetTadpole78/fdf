/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_map *map)
{
	t_line	*cur;
	t_line	*temp;

	cur = map->line;
	while (cur)
	{
		free(cur->point1);
		free(cur->point2);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	free(map);
}

void	add_to_map(t_map *map, t_line *line)
{
	t_line	*cur;

	if (!line)
		return ;
	if (!map->line)
	{
		map->line = line;
		return ;
	}
	cur = map->line;
	while (cur->next)
		cur = cur->next;
	line->previous = cur;
	cur->next = line;
}

static t_map	*init_map(char ***lines)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		return (NULL);
	}
	map->line = NULL;
	map->size = get_size(lines);
	init_points(map, lines);
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
