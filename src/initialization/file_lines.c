/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:41:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/07 17:26:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (0);
	*lines = malloc(sizeof(char *) * 2);
	if (!(*lines))
		return (0);
	line = get_next_line(*fd);
	if (!line)
	{
		free(*lines);
		return (0);
	}
	(*lines)[0] = ft_split(line, ' ');
	(*lines)[1] = NULL;
	free(line);
	if (!(*lines)[0])
	{
		free(*lines);
		return (0);
	}
	return (1);
}
