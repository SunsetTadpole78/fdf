/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:03:02 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/30 11:20:35 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_background(t_fdf *fdf, char *path)
{
	t_display_data	*dd;
	int	*a;
	static int	c = 0;

	a = malloc(sizeof(int));
	dd = fdf->display_data;
	printf("%p\n", dd->backgrounds);
	dd->backgrounds = ft_realloc(dd->backgrounds,
                        (c + 1) * sizeof(t_img *),
                        (c + 2) * sizeof(t_img *));
	dd->backgrounds[c] = malloc(sizeof(t_img));
	dd->backgrounds[c]->img = mlx_xpm_file_to_image(fdf->mlx, path, a, a);
	dd->backgrounds[c]->addr = mlx_get_data_addr(dd->backgrounds[c]->img, &dd->backgrounds[c]->bpp, &dd->backgrounds[c]->ll, &dd->backgrounds[c]->endian);
	dd->backgrounds[c + 1] = NULL;
	free(a);
	c++;
}

void	init_backgrounds(t_fdf *fdf)
{
	fdf->display_data->backgrounds = malloc(sizeof(t_img *));
	fdf->display_data->backgrounds[0] = NULL;
	add_background(fdf, "./resources/backgrounds/test.xpm");
	add_background(fdf, "./resources/backgrounds/gakarbou.xpm");
}

void	free_backgrounds(t_fdf *fdf)
{
	int	i;

	i = 0;
	printf("freee\n");
	while (fdf->display_data->backgrounds[i])
	{
		printf("%i", i);
		mlx_destroy_image(fdf->mlx, fdf->display_data->backgrounds[i]->img);
		free(fdf->display_data->backgrounds[i]);
		i++;
	}
	free(fdf->display_data->backgrounds);
}
