/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/30 09:27:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*f(t_fdf *v)
{
	static	t_fdf *fdf = NULL;
	
	if (v)
		fdf = v;
	return (fdf);
}

t_fdf	*get_fdf(void)
{
	return (f(NULL));
}

int	on_update(t_fdf *fdf)
{
	if (fdf->must_update || (active_navbar(2) && get_navbar()->must_update))
	{
		ft_memset(fdf->img.addr, 0, HEIGHT * WIDTH * (fdf->img.bpp / 8));
		draw_map(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img.img, 0, 0);
		update_buttons_texts(fdf);
		get_navbar()->must_update = 0;
		fdf->must_update = 0;
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
	f(fdf);
	if (!fdf)
	{
		ft_putstr_fd("Malloc Error\n", 2);
		return (2);
	}
	mlx_hook(fdf->window, 2, 1L << 0, keys_hook, fdf);
	mlx_loop_hook(fdf->mlx, on_update, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
