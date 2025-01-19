/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:45:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/19 11:39:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, t_vector2 pos, int color)
{
	char	*pixel;
	
	if (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT)
		return ;
	pixel = fdf->addr + ((int)pos.y * fdf->ll + (int)pos.x * (fdf->bpp / 8));
	*(unsigned int*)pixel = color;
}

void	rotate_x(t_fdf *fdf, t_vector3 *v3)
{
	int	tmp;
	float	alpha;

	alpha = fdf->display_data->rotate.x * (M_PI / 180);
	tmp = v3->y;
	v3->y = tmp * cos(alpha) - v3->z * sin(alpha);
	v3->z = tmp * sin(alpha) + v3->z * cos(alpha);
}

void	rotate_y(t_fdf *fdf, t_vector3 *v3)
{
	int	tmp;
	float	tetha;

	tetha = fdf->display_data->rotate.y * (M_PI / 180);
	tmp = v3->x;
	v3->x = tmp * cos(tetha) + v3->z * sin(tetha);
	v3->z = v3->z * cos(tetha) - tmp * sin(tetha);
}

void	rotate_z(t_fdf *fdf, t_vector3 *v3)
{
	int	tmp;
	float	gamma;

	gamma = fdf->display_data->rotate.z * (M_PI / 180);
	tmp = v3->x;
	v3->x = tmp * cos(gamma) - v3->y * sin(gamma);
	v3->y = tmp * sin(gamma) + v3->y * cos(gamma);
}

t_vector2	pixel_pos(t_fdf *fdf, t_vector3 v3)
{
	t_vector2	v2;
	int	zoom;

	zoom = fdf->display_data->zoom;
	v3.x *= zoom;
	v3.y *= zoom;
	v3.z *= zoom;

	v3.x -= fdf->display_data->a.x * zoom;
	v3.y -= fdf->display_data->a.y * zoom;
	v3.z -= fdf->display_data->a.z * zoom;

	rotate_x(fdf, &v3);
	rotate_y(fdf, &v3);
	rotate_z(fdf, &v3);

	v2.x = 700 + (v3.x - v3.z) * cos(30 * (M_PI / 180));
	v2.y = 500 + (v3.x + v3.z) * sin(30 * (M_PI / 180)) - v3.y;
	
	v2.x += fdf->display_data->pivot_point.x * zoom;
	v2.y += fdf->display_data->pivot_point.z * zoom;
	
	return (v2);
}

void	put_point(t_fdf *fdf, t_point *point)
{
	put_pixel(fdf, pixel_pos(fdf, point->pos), 0x00FF0000);
}

int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

void	draw_line(t_fdf *fdf, t_line *line)
{
	t_vector2	p1;
	t_vector2	p2;
	float	dx;
	float	dy;
	int	j;
	int	i;
	t_vector2	new;

	if (!line->point1)
	{
		put_point(fdf, line->point2);
		return ;
	}
	if (!line->point2)
	{
		put_point(fdf, line->point1);
		return ;
	}
	p1 = pixel_pos(fdf, line->point1->pos);
	p2 = pixel_pos(fdf, line->point2->pos);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;

	if (ft_abs(dx) > ft_abs(dy))
		j = ft_abs(dx);
	else
		j = ft_abs(dy);
	i = 0;
	while (i <= j)
	{
		new.x = p1.x + (dx * i) / j;
		new.y = p1.y + (dy * i) / j;
		put_pixel(fdf, new, 0xFFFFFF);
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_line	*cur;

	ft_memset(fdf->addr, 0, HEIGHT * WIDTH * (fdf->bpp / 8));
	cur = fdf->map->line;
	while (cur)
	{
		draw_line(fdf, cur);
		cur = cur->next;
	}
}

t_fdf	*create_window(t_map *map)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->ll, &fdf->endian);
	fdf->map = map;
	init_display_data(fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	return (fdf);
}
