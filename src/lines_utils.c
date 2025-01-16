/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:03 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:04 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	get_height(char ***lines)
{
	size_t	y;

	y = 0;
	while (lines[y])
		y++;
	return (y);
}

static size_t	get_width(char ***lines)
{
	size_t	x;

	if (!lines[0])
		return (0);
	x = 0;
	while (lines[0][x])
		x++;
	return (x);
}

t_vector2	get_size(char ***lines)
{
	return (vector2((float)get_width(lines), (float)get_height(lines)));
}
