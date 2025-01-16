/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 12:27:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	chars_to_float(char *nbr)
{
	float			res;
	unsigned int	i;
	unsigned int	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nbr[0] == '-')
	{
		i = 1;
		sign = -1;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}

void	free_point(t_point *point)
{
	free(point->pos);
	free(point);
}

void	free_map(t_map *map)
{
	t_line	*cur;
	t_line	*temp;

	cur = map->line;
	while (cur)
	{
		free_point(cur->point1);
		free_point(cur->point2);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	free(map->size);
	free(map);
}

size_t	get_height(char ***lines)
{
	size_t	y;

	y = 0;
	while (lines[y])
		y++;
	return (y);
}

size_t	get_width(char ***lines)
{
	size_t	x;

	if (!lines[0])
		return (0);
	x = 0;
	while (lines[0][x])
		x++;
	return (x);
}

t_vector2	*vector2(float x, float y)
{
	t_vector2	*v;

	v = malloc(sizeof(t_vector2));
	if (!v)
		return (NULL);
	v->x = x;
	v->y = y;
	return (v);
}

t_vector2	*get_size(char ***lines)
{
	return (vector2((float)get_width(lines), (float)get_height(lines)));
}

void	free_lines(char ****lines, int y)
{
	int	x;

	while (y >= 0)
	{
		if (*lines && (*lines)[y])
		{
			x = 0;
			while ((*lines)[y][x])
			{
				free((*lines)[y][x]);
				x++;
			}
			free((*lines)[y]);
		}
		y--;
	}
	free(*lines);
}

int	init_lines(char *path, char ****lines, int *fd)
{
	char	*line;

	*lines = malloc(sizeof(char *) * 2);
	if (!(*lines))
		return (0);
	*fd = open(path, O_RDONLY);
	line = get_next_line(*fd);
	if (!line)
	{
		free(*lines);
		return (0);
	}
	(*lines)[0] = ft_split(line, ' ');
	free(line);
	if (!(*lines)[0])
	{
		free(*lines);
		return (0);
	}
	return (1);
}

int	add_line(char *line, char ****lines, int y)
{
	char	***temp;
	size_t	size;

	if (!line)
		return (0);
	size = sizeof(char *) * (y + 1);
	temp = ft_realloc(*lines, size, size + sizeof(char *));
	if (!temp)
	{
		free_lines(lines, y);
		return (-1);
	}
	temp[y + 1] = NULL;
	*lines = temp;
	(*lines)[y] = ft_split(line, ' ');
	if (!(*lines)[y])
	{
		free_lines(lines, y);
		return (-1);
	}
	free(line);
	return (1);
}

t_point	*init_point(char ***lines, t_vector2 *p)
{
	t_point	*point;

	if (!lines[(size_t)p->y] || !lines[(size_t)p->y][(size_t)p->x])
	{
		free(p);
		return (NULL);
	}
	point = malloc(sizeof(t_point));
	if (!point)
	{
		free(p);
		return (NULL);
	}
	point->pos = malloc(sizeof(t_vector3));
	if (!point->pos)
	{
		free(point);
		free(p);
		return (NULL);
	}
	point->pos->x = p->x;
	point->pos->y = chars_to_float(lines[(size_t)p->y][(size_t)p->x]);
	point->pos->z = p->y;
	free(p);
	return (point);
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

t_line	*init_line(char ***lines, t_vector2 *p1, t_vector2 *p2)
{
	t_line	*line;

	if (!p1 || !p2)
		return (NULL);
	line = malloc(sizeof(t_line));
	if (!line)
		return (0);
	line->previous = NULL;
	line->next = NULL;
	line->point1 = init_point(lines, p1);
	if (!line->point1)
	{
		free(line);
		free(p2);
		return (NULL);
	}
	line->point2 = init_point(lines, p2);
	if (!line->point2)
	{
		free_point(line->point1);
		free(line);
		return (NULL);
	}
	return (line);
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
			line = init_line(lines, vector2(x, y), vector2(x, y + 1));
			if (!line && lines[y + 1] && lines[y + 1][x])
				return (0);
			add_to_map(map, line);
			line = init_line(lines, vector2(x, y), vector2(x + 1, y));
			if (!line && lines[y] && lines[y][x + 1])
				return (0);
			add_to_map(map, line);
			x++;
		}
		y++;
	}
	return (1);
}

t_map	*init_map(char ***lines)
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

	(void)path;
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

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map_path>\n", 2);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Map not found\n", 2);
		return (1);
	}
	free_map(map);
}
