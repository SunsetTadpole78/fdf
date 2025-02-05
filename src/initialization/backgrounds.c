/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:03:02 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 17:06:38 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_background(t_fdf *fdf, char *path)
{
	t_background	*dd;
	static int	c = 0;

	dd = fdf->background;
	printf("%p\n", dd->backgrounds);
	dd->backgrounds = ft_realloc(dd->backgrounds,
                        (c + 1) * sizeof(t_img *),
                        (c + 2) * sizeof(t_img *));
	dd->backgrounds[c] = malloc(sizeof(t_img));
	dd->backgrounds[c]->img = mlx_xpm_file_to_image(fdf->mlx, path, &dd->backgrounds[c]->width, &dd->backgrounds[c]->height);
	dd->backgrounds[c]->addr = mlx_get_data_addr(dd->backgrounds[c]->img, &dd->backgrounds[c]->bpp, &dd->backgrounds[c]->ll, &dd->backgrounds[c]->endian);
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
}

void	free_backgrounds(t_fdf *fdf)
{
	int	i;

	i = 0;
	printf("freee\n");
	while (fdf->background->backgrounds[i])
	{
		printf("%i", i);
		mlx_destroy_image(fdf->mlx, fdf->background->backgrounds[i]->img);
		free(fdf->background->backgrounds[i]);
		i++;
	}
	free(fdf->background->backgrounds);
}
