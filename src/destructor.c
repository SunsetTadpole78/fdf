/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:22:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 11:54:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	destruct(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	if (fdf->background->bg.img)
		mlx_destroy_image(fdf->mlx, fdf->background->bg.img);
	free_backgrounds(fdf);
	mlx_clear_window(fdf->mlx, fdf->window);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free_map(fdf->map);
	free_navbar();
	free(fdf->background);
	free_contr(fdf->isometric.controls);
	free_contr(fdf->conic.controls);
	free_contr(fdf->parallel.controls);
	free_depth(fdf);
	free(fdf);
	exit(EXIT_SUCCESS);
}

int	on_close(t_fdf *fdf)
{
	destruct(fdf);
	return (1);
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

void	free_map(t_map *map)
{
	size_t	y;

	if (!map->points)
		return ;
	y = 0;
	while (map->points[y])
	{
		free(map->points[y]);
		y++;
	}
	free(map->points);
	free(map);
}
