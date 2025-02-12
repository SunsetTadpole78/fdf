/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:03:02 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 13:58:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_background(t_fdf *fdf, char *path)
{
	t_background	*dd;
	static int		c = 0;

	dd = fdf->background;
	dd->backgrounds = ft_realloc(dd->backgrounds,
			(c + 1) * sizeof(t_img *),
			(c + 2) * sizeof(t_img *));
	dd->backgrounds[c] = malloc(sizeof(t_img));
	dd->backgrounds[c]->img = mlx_xpm_file_to_image(fdf->mlx, path,
			&dd->backgrounds[c]->width, &dd->backgrounds[c]->height);
	dd->backgrounds[c]->addr = mlx_get_data_addr(dd->backgrounds[c]->img,
			&dd->backgrounds[c]->bpp, &dd->backgrounds[c]->ll,
			&dd->backgrounds[c]->endian);
	dd->backgrounds[c + 1] = NULL;
	c++;
}

void	init_backgrounds(t_fdf *fdf)
{
	fdf->background = malloc(sizeof(t_background));
	fdf->background->bg_color = NULL;
	fdf->background->bg.img = NULL;
	fdf->background->backgrounds = malloc(sizeof(t_img *));
	fdf->background->backgrounds[0] = NULL;
	add_background(fdf, "./resources/backgrounds/test.xpm");
	add_background(fdf, "./resources/backgrounds/gakarbou.xpm");
	add_background(fdf, "./resources/backgrounds/montain.xpm");
	add_background(fdf, "./resources/backgrounds/neon.xpm");
	add_background(fdf, "./resources/backgrounds/win.xpm");
	add_background(fdf, "./resources/backgrounds/ft.xpm");
	add_background(fdf, "./resources/backgrounds/rick.xpm");
	add_background(fdf, "./resources/backgrounds/larry.xpm");
	add_background(fdf, "./resources/backgrounds/hello_kitty.xpm");
}

void	free_backgrounds(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (fdf->background->backgrounds[i])
	{
		mlx_destroy_image(fdf->mlx, fdf->background->backgrounds[i]->img);
		free(fdf->background->backgrounds[i]);
		i++;
	}
	free(fdf->background->backgrounds);
}
