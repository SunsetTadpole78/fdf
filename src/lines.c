/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:41:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*build_line(char ***lines, t_vector2 p1, t_vector2 p2)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (0);
	line->previous = NULL;
	line->next = NULL;
	line->point1 = init_point(lines, p1);
	if (!line->point1)
	{
		free(line);
		return (NULL);
	}
	line->point2 = init_point(lines, p2);
	if (!line->point2)
	{
		free(line->point1);
		free(line);
		return (NULL);
	}
	return (line);
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
