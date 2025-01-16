/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 18:04:37 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	(void)fdf;
	if (keycode == XK_Escape)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_clear_window(fdf->mlx, fdf->window);
		mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		free_map(fdf->map);
		free(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_fdf	*fdf;

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
	fdf = create_window(map);
	if (!fdf)
	{
		ft_putstr_fd("Malloc Error\n", 2);
		return (2);
	}
	mlx_hook(fdf->window, 2, 1L << 0, key_hook, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
