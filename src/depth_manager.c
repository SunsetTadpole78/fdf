/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:40:18 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:33:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_depth(t_fdf *fdf)
{
	int	y;

	fdf->depth = malloc(sizeof(int *) * height());
	if (!fdf->depth)
		return ;
	y = 0;
	while (y < height())
	{
		fdf->depth[y] = malloc(sizeof(int) * width());
		if (!fdf->depth[y])
		{
			while (--y >= 0)
				free(fdf->depth[y]);
			free(fdf->depth);
			fdf->depth = NULL;
			return ;
		}
		y++;
	}
}

void	clear_depth(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < height())
	{
		x = 0;
		while (x < width())
		{
			fdf->depth[y][x] = MIN_INT;
			x++;
		}
		y++;
	}
}

void	free_depth(t_fdf *fdf)
{
	int	y;

	if (!fdf->depth)
		return ;
	y = 0;
	while (y < height())
	{
		if (fdf->depth[y])
			free(fdf->depth[y]);
		y++;
	}
	free(fdf->depth);
	fdf->depth = NULL;
}
